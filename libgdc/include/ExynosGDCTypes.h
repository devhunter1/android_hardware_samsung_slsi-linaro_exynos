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

#ifndef EXYNOS_GDC_TYPES_H
#define EXYNOS_GDC_TYPES_H

#include <string.h>

#define GDC_MAX_PLANES              3
#define GDC_BUF_MAX_PLANE           4 //Image planes(3) + Metadata plane(1)
#define GDC_GRID_MAX_WIDTH          33
#define GDC_GRID_MAX_HEIGHT         33
#define GDC_GRID_BYTE_SIZE          (sizeof(int32_t) * GDC_GRID_MAX_WIDTH * GDC_GRID_MAX_HEIGHT)

/* log */
#define GDC_LOG_PREFIX  "[LIB_GDC][%s:%d]"

#define GDC_LOG_COMMON(_prio, _fmt, ...)                                                        \
    do {                                                                                        \
        if (_prio == ANDROID_LOG_VERBOSE) {                                                     \
            ALOGV(GDC_LOG_PREFIX _fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__);                      \
        } else {                                                                                \
            LOG_PRI(_prio, LOG_TAG, GDC_LOG_PREFIX _fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__);    \
        }                                                                                       \
    } while(0)

#define GDC_LOGV(fmt, ...)  \
    GDC_LOG_COMMON(ANDROID_LOG_VERBOSE, fmt, ##__VA_ARGS__)

#define GDC_LOGI(fmt, ...)  \
    GDC_LOG_COMMON(ANDROID_LOG_INFO, fmt, ##__VA_ARGS__)

#define GDC_LOGD(fmt, ...)  \
    GDC_LOG_COMMON(ANDROID_LOG_DEBUG, fmt, ##__VA_ARGS__)

#define GDC_LOGW(fmt, ...)  \
    GDC_LOG_COMMON(ANDROID_LOG_WARN, fmt, ##__VA_ARGS__)

#define GDC_LOGE(fmt, ...)  \
    GDC_LOG_COMMON(ANDROID_LOG_ERROR, fmt, ##__VA_ARGS__)

#define GDC_LOG_FATAL(fmt, ...)  \
    GDC_LOG_COMMON(ANDROID_LOG_FATAL, fmt, ##__VA_ARGS__)

enum GDC_pixel_size {
    GDC_PIXEL_SIZE_8BIT = 0,
    GDC_PIXEL_SIZE_10BIT,
    GDC_PIXEL_SIZE_PACKED_10BIT,
    GDC_PIXEL_SIZE_8_2BIT,
    GDC_PIXEL_SIZE_12BIT,
    GDC_PIXEL_SIZE_13BIT,
    GDC_PIXEL_SIZE_16BIT,
    GDC_PIXEL_SIZE_PACKED_12BIT_COMP,
};

enum GDC_pixel_comp_info {
    GDC_NO_COMP = 0,
    GDC_COMP,
    GDC_COMP_64B = GDC_COMP,
    GDC_COMP_LOSS,
    GDC_COMP_LOSS_64B = GDC_COMP_LOSS,
};

enum ExynosGDCConnection {
    EXYNOS_GDC_MFC_CONNECTTION_M2M,
    EXYNOS_GDC_MFC_CONNECTTION_OTF,
    EXYNOS_GDC_MFC_CONNECTTION_VIRTUAL_OTF,
    EXYNOS_GDC_MFC_CONNECTTION_NONE,
};

enum GDC_out_mode {
    GDC_OUT_M2M = 0,
    GDC_OUT_VOTF,
    GDC_OUT_OTF,
};

/* Pixel_size[0:5] and pixel_comp[6:7] */
#define GET_PIXEL_FLAG(a, b) (((b & 0x3) << 6) | (a & 0x3F))

struct ExynosGDCGridTable
{
    int32_t gridX[GDC_GRID_MAX_HEIGHT][GDC_GRID_MAX_WIDTH];
    int32_t gridY[GDC_GRID_MAX_HEIGHT][GDC_GRID_MAX_WIDTH];
    uint32_t width;
    uint32_t height;

    ExynosGDCGridTable() {
        memset(gridX, 0x00, GDC_GRID_BYTE_SIZE);
        memset(gridY, 0x00, GDC_GRID_BYTE_SIZE);
        width = GDC_GRID_MAX_WIDTH;
        height = GDC_GRID_MAX_HEIGHT;
    }

    ExynosGDCGridTable& operator =(const ExynosGDCGridTable &other) {
        for (int i = 0; i < other.height; i++) {
            for (int j = 0; j < other.width; j++) {
                this->gridX[i][j] = other.gridX[i][j];
                this->gridY[i][j] = other.gridY[i][j];
            }
        }
        this->width = other.width;
        this->height = other.height;

        return *this;
    }
};

struct ExynosGDCSizeParam
{
    uint32_t cropX;
    uint32_t cropY;
    uint32_t cropW;
    uint32_t cropH;
    uint32_t fullW;
    uint32_t fullH;

    ExynosGDCSizeParam() {
        cropX = 0;
        cropY = 0;
        cropW = 0;
        cropH = 0;
        fullW = 0;
        fullH = 0;
    }

    ExynosGDCSizeParam& operator =(const ExynosGDCSizeParam &other) {
        this->cropX = other.cropX;
        this->cropY = other.cropY;
        this->cropW = other.cropW;
        this->cropH = other.cropH;
        this->fullW = other.fullW;
        this->fullH = other.fullH;

        return *this;
    }
};

struct ExynosGDCPlane {
    int32_t fd;
    uint32_t length;

    ExynosGDCPlane() {
        fd = -1;
        length = 0;
    }

    ExynosGDCPlane& operator =(const ExynosGDCPlane &other) {
        this->fd = other.fd;
        this->length = other.length;

        return *this;
    }
};

struct ExynosGDCBuf {
    uint32_t index;
    uint32_t planeCount;
    struct ExynosGDCPlane planes[GDC_BUF_MAX_PLANE];
    enum ExynosGDCConnection HWConnection;
    uint32_t bytesperline[GDC_MAX_PLANES];
    bool gridMode;
    bool bypassMode;
    bool downscaleMode;

    ExynosGDCBuf() {
        index = 0;
        planeCount = 0;
        HWConnection = EXYNOS_GDC_MFC_CONNECTTION_M2M;
        gridMode = false;
        bypassMode = false;
        downscaleMode = false;
        for (int i = 0; i < GDC_MAX_PLANES; i++) {
            bytesperline[i] = 0;
        }
    }

    ExynosGDCBuf& operator =(const ExynosGDCBuf &other) {
        this->index = other.index;
        this->planeCount = other.planeCount;
        for (uint32_t planeIndex = 0; planeIndex < GDC_BUF_MAX_PLANE; planeIndex++) {
            this->planes[planeIndex] = other.planes[planeIndex];
        }

        this->HWConnection = other.HWConnection;
        this->gridMode = other.gridMode;
        this->bypassMode = other.bypassMode;
        this->downscaleMode = other.downscaleMode;

        for (int i = 0; i < GDC_MAX_PLANES; i++) {
            this->bytesperline[i] = other.bytesperline[i];
        }
        return *this;
    }
};

#endif //EXYNOS_GDC_TYPES_H
