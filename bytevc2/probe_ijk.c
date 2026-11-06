/* IJK 链路探针（CI probe-x86 job 用）：验证 demuxer→codec 全链
 * ① mov.c 的 bv2C 子 box → codec_id 切到 AV_CODEC_ID_BYTEVC2；
 * ② avcodec_descriptor_get(BYTEVC2) 命中（0x21004 大值 bsearch 排序）；
 * ③ avcodec_find_decoder(BYTEVC2) 命中（allcodecs 注册）。
 * 与 mpv 链 probe.c 差异：find_stream_info 失败（stub 无帧）不阻断——
 * codec_id 在 avformat_open_input 的 demuxer 层已定，仍需打印流信息。
 * 断言哨兵 PROBE_OK=1，CI grep 判定。
 * 用法: probe_ijk <bvc2_plain.mp4> */
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    AVFormatContext *fc = NULL;
    int ret, ok = 0;

    if (argc < 2) {
        printf("PROBE usage: probe_ijk <file>\n");
        return 1;
    }

    const AVCodecDescriptor *desc =
        avcodec_descriptor_get(AV_CODEC_ID_BYTEVC2);
    printf("PROBE DESC ptr=%p name=%s\n",
           (void *)desc, desc ? desc->name : "NULL");

    const AVCodec *dec = avcodec_find_decoder(AV_CODEC_ID_BYTEVC2);
    printf("PROBE DECODER ptr=%p name=%s\n",
           (void *)dec, dec ? dec->name : "NULL");

    ret = avformat_open_input(&fc, argv[1], NULL, NULL);
    if (ret < 0) {
        printf("PROBE open failed: %d\n", ret);
        return 1;
    }
    ret = avformat_find_stream_info(fc, NULL);
    printf("PROBE find_stream_info ret=%d (stub 无帧可为负)\n", ret);

    for (unsigned i = 0; i < fc->nb_streams; i++) {
        AVStream *st = fc->streams[i];
        printf("PROBE stream[%u] type=%d codec_id=%d codec_tag=%08X name=%s extradata_size=%d\n",
               i, st->codecpar->codec_type, st->codecpar->codec_id,
               st->codecpar->codec_tag,
               avcodec_get_name(st->codecpar->codec_id),
               st->codecpar->extradata_size);
        if (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
            ok = (st->codecpar->codec_id == AV_CODEC_ID_BYTEVC2) &&
                 (desc != NULL) && (dec != NULL);
    }
    printf("PROBE IDS bytevc2=%d hevc=%d\n",
           (int)AV_CODEC_ID_BYTEVC2, (int)AV_CODEC_ID_HEVC);
    printf("PROBE_OK=%d\n", ok);
    avformat_close_input(&fc);
    return ok ? 0 : 1;
}
