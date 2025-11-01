/*
 * Copyright@ Samsung Electronics Co. LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __LINUX_VIDEODEV2_EXYNOS_GDC_H
#define __LINUX_VIDEODEV2_EXYNOS_GDC_H

#include "linux/videodev2_exynos_media.h"

#define V4L2_CID_CAMERAPP_BASE      (V4L2_CTRL_CLASS_CAMERA | 0x4000)

/* Camera-PostProcessign IOCTL */
#define V4L2_CID_CAMERAPP_SENSOR_NUM            (V4L2_CID_CAMERAPP_BASE+1)
#define V4L2_CID_CAMERAPP_GDC_GRID_CROP_START   (V4L2_CID_CAMERAPP_BASE+2)
#define V4L2_CID_CAMERAPP_GDC_GRID_CROP_SIZE    (V4L2_CID_CAMERAPP_BASE+3)
#define V4L2_CID_CAMERAPP_GDC_GRID_SENSOR_SIZE  (V4L2_CID_CAMERAPP_BASE+4)
#define V4L2_CID_CAMERAPP_GDC_GRID_CONTROL      (V4L2_CID_CAMERAPP_BASE+5)

/* 12 Y/CbCr 4:2:0 SBWC Lossy v2.7 32B/64B align */
#ifndef V4L2_PIX_FMT_NV12M_SBWCL_32_8B
#define V4L2_PIX_FMT_NV12M_SBWCL_32_8B    v4l2_fourcc('M', '1', 'L', '3')
#endif
#ifndef V4L2_PIX_FMT_NV12M_SBWCL_32_10B
#define V4L2_PIX_FMT_NV12M_SBWCL_32_10B   v4l2_fourcc('M', '1', 'L', '4')
#endif
#ifndef V4L2_PIX_FMT_NV12M_SBWCL_64_8B
#define V4L2_PIX_FMT_NV12M_SBWCL_64_8B    v4l2_fourcc('M', '1', 'L', '6')
#endif
#ifndef V4L2_PIX_FMT_NV12M_SBWCL_64_10B
#define V4L2_PIX_FMT_NV12M_SBWCL_64_10B   v4l2_fourcc('M', '1', 'L', '7')
#endif

/* 12 Y/CbCr 4:2:0 SBWC Lossy v2.7 single 32B/64B align */
#ifndef V4L2_PIX_FMT_NV12N_SBWCL_32_8B
#define V4L2_PIX_FMT_NV12N_SBWCL_32_8B    v4l2_fourcc('N', '1', 'L', '3')
#endif
#ifndef V4L2_PIX_FMT_NV12N_SBWCL_32_10B
#define V4L2_PIX_FMT_NV12N_SBWCL_32_10B   v4l2_fourcc('N', '1', 'L', '4')
#endif
#ifndef V4L2_PIX_FMT_NV12N_SBWCL_64_8B
#define V4L2_PIX_FMT_NV12N_SBWCL_64_8B    v4l2_fourcc('N', '1', 'L', '6')
#endif
#ifndef V4L2_PIX_FMT_NV12N_SBWCL_64_10B
#define V4L2_PIX_FMT_NV12N_SBWCL_64_10B   v4l2_fourcc('N', '1', 'L', '7')
#endif

/* for V4L2_CID_CAMERAPP_GDC_GRID_CONTROL */
struct gdc_crop_param {
    uint32_t sensor_num;
    uint32_t sensor_width;
    uint32_t sensor_height;
    uint32_t crop_start_x;
    uint32_t crop_start_y;
    uint32_t crop_width;
    uint32_t crop_height;
    bool is_crop_dzoom;
    bool is_scaled;
    bool use_calculated_grid;
    int calculated_grid_x[33][33];
    int calculated_grid_y[33][33];
    uint32_t src_bytesperline[3];
    uint32_t dst_bytesperline[3];
    uint32_t buf_Index;
    bool votf_en;        // Deprecated from v11.0
    bool is_grid_mode;   // 0:input buffer 1:output buffer
    bool is_bypass_mode; // 0:off, 1:on
    char out_mode;
    int reserved[24];
};

struct gdc_metadata {
    uint32_t full_width;
    uint32_t full_height;
    uint32_t pixel_format;
};

// Private Pixel Format from exynos definition
// hardware/samsung_slsi/exynos/include/exynos_format.h
enum class gdc_pixel_format : int {
    HAL_PIXEL_FORMAT_EXYNOS_YCbCr_420_SP_M_SBWC         = 0x130,
    HAL_PIXEL_FORMAT_EXYNOS_YCbCr_420_SP_M_10B_SBWC     = 0x132,
    HAL_PIXEL_FORMAT_EXYNOS_YCrCb_420_SP_M_SBWC         = 0x134,
    HAL_PIXEL_FORMAT_EXYNOS_YCrCb_420_SP_M_10B_SBWC     = 0x135,
    HAL_PIXEL_FORMAT_EXYNOS_YCbCr_420_SP_M_SBWC_L50     = 0x140,
    HAL_PIXEL_FORMAT_EXYNOS_YCbCr_420_SP_M_SBWC_L75     = 0x141,
    HAL_PIXEL_FORMAT_EXYNOS_YCbCr_420_SP_M_10B_SBWC_L40 = 0x160,
    HAL_PIXEL_FORMAT_EXYNOS_YCbCr_420_SP_M_10B_SBWC_L60 = 0x161,
    HAL_PIXEL_FORMAT_EXYNOS_YCbCr_420_SP_M_10B_SBWC_L80 = 0x162,
    HAL_PIXEL_FORMAT_EXYNOS_420_SP_M_32_SBWC_L          = 0x180,
    HAL_PIXEL_FORMAT_EXYNOS_420_SP_M_64_SBWC_L          = 0x181,
    HAL_PIXEL_FORMAT_EXYNOS_420_SPN_32_SBWC_L           = 0x190,
    HAL_PIXEL_FORMAT_EXYNOS_420_SPN_64_SBWC_L           = 0x191,
    HAL_PIXEL_FORMAT_EXYNOS_420_SP_M_10B_32_SBWC_L      = 0x200,
    HAL_PIXEL_FORMAT_EXYNOS_420_SP_M_10B_64_SBWC_L      = 0x201,
    HAL_PIXEL_FORMAT_EXYNOS_420_SPN_10B_32_SBWC_L       = 0x210,
    HAL_PIXEL_FORMAT_EXYNOS_420_SPN_10B_64_SBWC_L       = 0x211,
};

#endif //EXYNOS_GDC_H
