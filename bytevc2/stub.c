/* byteVC2dec 桩实现：仅供 x86 probe CI 验证 demuxer/desc 链路时
 * 链接 bytevc2 解码器（arm64 私有库无法在 x86 载入）。
 * decode 恒返 0 且 got_frame=0（pointer info 全 NULL）——不产生帧，
 * find_stream_info 正常耗尽样本后返回，codec_id 保持 demuxer 层结果。 */
#include "bytevc2_api.h"
#include <stdlib.h>
#include <string.h>

void byteVC2_set_log_callback(byteVC2_log_cb cb, void *userdata)
{
    (void)cb; (void)userdata;
}

void byteVC2dec_get_version(char *out) { strcpy(out, "stub"); }

byteVC2dec_param *byteVC2dec_get_default_param(void) { return calloc(1, 0x70); }
void byteVC2dec_release_param(byteVC2dec_param *param) { free(param); }
void byteVC2dec_print_param(const byteVC2dec_param *param) { (void)param; }

int byteVC2dec_set_param_integer_info(byteVC2dec_param *param, const char *key, int value)
{ (void)param; (void)key; (void)value; return 0; }
int byteVC2dec_set_param_float_info(byteVC2dec_param *param, const char *key, float value)
{ (void)param; (void)key; (void)value; return 0; }
int byteVC2dec_set_param_pointer_info(byteVC2dec_param *param, const char *key, void *value)
{ (void)param; (void)key; (void)value; return 0; }

byteVC2dec_ctx *byteVC2dec_create(const byteVC2dec_param *param) { (void)param; return calloc(1, 0x2808); }
void byteVC2dec_destroy(byteVC2dec_ctx *ctx) { free(ctx); }
int byteVC2dec_reconfig(byteVC2dec_ctx *ctx, const byteVC2dec_param *param)
{ (void)ctx; (void)param; return 0; }

byteVC2dec_packet *byteVC2dec_alloc_packet(void) { return calloc(1, 0x58); }
void byteVC2dec_release_packet(byteVC2dec_packet *pkt) { free(pkt); }
int byteVC2dec_set_packet_integer_info(byteVC2dec_packet *pkt, const char *key, int64_t value)
{ (void)pkt; (void)key; (void)value; return 0; }
int byteVC2dec_set_packet_float_info(byteVC2dec_packet *pkt, const char *key, float value)
{ (void)pkt; (void)key; (void)value; return 0; }
int byteVC2dec_set_packet_pointer_info(byteVC2dec_packet *pkt, const char *key, void *value)
{ (void)pkt; (void)key; (void)value; return 0; }

byteVC2dec_frame *byteVC2dec_alloc_frame(void) { return calloc(1, 0x98); }
void byteVC2dec_release_frame(byteVC2dec_frame *frame) { free(frame); }
int64_t byteVC2dec_get_frame_integer_info(const byteVC2dec_frame *frame, const char *key, int idx)
{ (void)frame; (void)key; (void)idx; return 0; }
void *byteVC2dec_get_frame_pointer_info(const byteVC2dec_frame *frame, const char *key, int idx)
{ (void)frame; (void)key; (void)idx; return NULL; }
float byteVC2dec_get_frame_float_info(const byteVC2dec_frame *frame, const char *key)
{ (void)frame; (void)key; return 0.0f; }

int byteVC2dec_send_packet(byteVC2dec_ctx *ctx, byteVC2dec_packet *pkt)
{ (void)ctx; (void)pkt; return 0; }
int byteVC2dec_decode(byteVC2dec_ctx *ctx, byteVC2dec_packet *pkt, byteVC2dec_frame *frame)
{ (void)ctx; (void)pkt; (void)frame; return 0; }
int byteVC2dec_get_frame(byteVC2dec_ctx *ctx, byteVC2dec_frame *frame)
{ (void)ctx; (void)frame; return 0; }
int byteVC2dec_return_frame(byteVC2dec_ctx *ctx, byteVC2dec_frame *frame)
{ (void)ctx; (void)frame; return 0; }
int byteVC2dec_get_sr_frame(byteVC2dec_ctx *ctx, byteVC2dec_frame *frame)
{ (void)ctx; (void)frame; return 0; }
int byteVC2dec_flush(byteVC2dec_ctx *ctx, int flags) { (void)ctx; (void)flags; return 0; }
int byteVC2dec_flush_keep_buffer(byteVC2dec_ctx *ctx) { (void)ctx; return 0; }

int byteVC2_get_next_access_unit(const uint8_t *buf, int len) { (void)buf; (void)len; return 0; }
void byteVC2dec_dump_video_info(byteVC2dec_ctx *ctx) { (void)ctx; }
void byteVC2dec_dump_decoding_status(byteVC2dec_ctx *ctx) { (void)ctx; }
