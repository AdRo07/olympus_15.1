/*
 * soc-camera media bus helper routines
 *
 * Copyright (C) 2009, Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/module.h>

#include <media/v4l2-device.h>
#include <media/v4l2-mediabus.h>
#include <media/soc_mediabus.h>

static const struct soc_mbus_lookup mbus_fmt[] = {
{
	.code = V4L2_MBUS_FMT_YUYV8_2X8,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_YUYV,
		.name			= "YUYV",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_2X8_PADHI,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_YVYU8_2X8,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_YVYU,
		.name			= "YVYU",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_2X8_PADHI,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_UYVY8_2X8,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_UYVY,
		.name			= "UYVY",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_2X8_PADHI,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_VYUY8_2X8,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_VYUY,
		.name			= "VYUY",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_2X8_PADHI,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_RGB555_2X8_PADHI_LE,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_RGB555,
		.name			= "RGB555",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_2X8_PADHI,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_RGB555_2X8_PADHI_BE,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_RGB555X,
		.name			= "RGB555X",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_2X8_PADHI,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_RGB565_2X8_LE,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_RGB565,
		.name			= "RGB565",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_2X8_PADHI,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_RGB565_2X8_BE,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_RGB565X,
		.name			= "RGB565X",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_2X8_PADHI,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_SBGGR8_1X8,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_SBGGR8,
		.name			= "Bayer 8 BGGR",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_NONE,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_SBGGR10_1X10,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_SBGGR10,
		.name			= "Bayer 10 BGGR",
		.bits_per_sample	= 10,
		.packing		= SOC_MBUS_PACKING_EXTEND16,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_Y8_1X8,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_GREY,
		.name			= "Grey",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_NONE,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_Y10_1X10,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_Y10,
		.name			= "Grey 10bit",
		.bits_per_sample	= 10,
		.packing		= SOC_MBUS_PACKING_EXTEND16,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_SBGGR10_2X8_PADHI_LE,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_SBGGR10,
		.name			= "Bayer 10 BGGR",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_2X8_PADHI,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_SBGGR10_2X8_PADLO_LE,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_SBGGR10,
		.name			= "Bayer 10 BGGR",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_2X8_PADLO,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_SBGGR10_2X8_PADHI_BE,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_SBGGR10,
		.name			= "Bayer 10 BGGR",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_2X8_PADHI,
		.order			= SOC_MBUS_ORDER_BE,
	},
}, {
	.code = V4L2_MBUS_FMT_SBGGR10_2X8_PADLO_BE,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_SBGGR10,
		.name			= "Bayer 10 BGGR",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_2X8_PADLO,
		.order			= SOC_MBUS_ORDER_BE,
	},
}, {
	.code = V4L2_MBUS_FMT_JPEG_1X8,
	.fmt = {
		.fourcc                 = V4L2_PIX_FMT_JPEG,
		.name                   = "JPEG",
		.bits_per_sample        = 8,
		.packing                = SOC_MBUS_PACKING_VARIABLE,
		.order                  = SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_RGB444_2X8_PADHI_BE,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_RGB444,
		.name			= "RGB444",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_2X8_PADHI,
		.order			= SOC_MBUS_ORDER_BE,
	},
}, {
	.code = V4L2_MBUS_FMT_YUYV8_1_5X8,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_YUV420,
		.name			= "YUYV 4:2:0",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_1_5X8,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_YVYU8_1_5X8,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_YVU420,
		.name			= "YVYU 4:2:0",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_1_5X8,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_UYVY8_1X16,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_UYVY,
		.name			= "UYVY 16bit",
		.bits_per_sample	= 16,
		.packing		= SOC_MBUS_PACKING_EXTEND16,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_VYUY8_1X16,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_VYUY,
		.name			= "VYUY 16bit",
		.bits_per_sample	= 16,
		.packing		= SOC_MBUS_PACKING_EXTEND16,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_YUYV8_1X16,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_YUYV,
		.name			= "YUYV 16bit",
		.bits_per_sample	= 16,
		.packing		= SOC_MBUS_PACKING_EXTEND16,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_YVYU8_1X16,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_YVYU,
		.name			= "YVYU 16bit",
		.bits_per_sample	= 16,
		.packing		= SOC_MBUS_PACKING_EXTEND16,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_SGRBG8_1X8,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_SGRBG8,
		.name			= "Bayer 8 GRBG",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_NONE,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_SGRBG10_DPCM8_1X8,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_SGRBG10DPCM8,
		.name			= "Bayer 10 BGGR DPCM 8",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_NONE,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_SGBRG10_1X10,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_SGBRG10,
		.name			= "Bayer 10 GBRG",
		.bits_per_sample	= 10,
		.packing		= SOC_MBUS_PACKING_EXTEND16,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_SGRBG10_1X10,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_SGRBG10,
		.name			= "Bayer 10 GRBG",
		.bits_per_sample	= 10,
		.packing		= SOC_MBUS_PACKING_EXTEND16,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_SRGGB10_1X10,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_SRGGB10,
		.name			= "Bayer 10 RGGB",
		.bits_per_sample	= 10,
		.packing		= SOC_MBUS_PACKING_EXTEND16,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_SBGGR12_1X12,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_SBGGR12,
		.name			= "Bayer 12 BGGR",
		.bits_per_sample	= 12,
		.packing		= SOC_MBUS_PACKING_EXTEND16,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_SGBRG12_1X12,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_SGBRG12,
		.name			= "Bayer 12 GBRG",
		.bits_per_sample	= 12,
		.packing		= SOC_MBUS_PACKING_EXTEND16,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_SGRBG12_1X12,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_SGRBG12,
		.name			= "Bayer 12 GRBG",
		.bits_per_sample	= 12,
		.packing		= SOC_MBUS_PACKING_EXTEND16,
		.order			= SOC_MBUS_ORDER_LE,
	},
}, {
	.code = V4L2_MBUS_FMT_SRGGB12_1X12,
	.fmt = {
		.fourcc			= V4L2_PIX_FMT_SRGGB12,
		.name			= "Bayer 12 RGGB",
		.bits_per_sample	= 12,
		.packing		= SOC_MBUS_PACKING_EXTEND16,
		.order			= SOC_MBUS_ORDER_LE,
	},
},
};

int soc_mbus_samples_per_pixel(const struct soc_mbus_pixelfmt *mf,
			unsigned int *numerator, unsigned int *denominator)
{
	switch (mf->packing) {
	case SOC_MBUS_PACKING_NONE:
	case SOC_MBUS_PACKING_EXTEND16:
		*numerator = 1;
		*denominator = 1;
		return 0;
	case SOC_MBUS_PACKING_2X8_PADHI:
	case SOC_MBUS_PACKING_2X8_PADLO:
		*numerator = 2;
		*denominator = 1;
		return 0;
	case SOC_MBUS_PACKING_1_5X8:
		*numerator = 3;
		*denominator = 2;
		return 0;
	case SOC_MBUS_PACKING_VARIABLE:
		*numerator = 0;
		*denominator = 1;
		return 0;
	}
	return -EINVAL;
}
EXPORT_SYMBOL(soc_mbus_samples_per_pixel);

s32 soc_mbus_bytes_per_line(u32 width, const struct soc_mbus_pixelfmt *mf)
{
	switch (mf->packing) {
	case SOC_MBUS_PACKING_NONE:
		return width * mf->bits_per_sample / 8;
	case SOC_MBUS_PACKING_2X8_PADHI:
	case SOC_MBUS_PACKING_2X8_PADLO:
	case SOC_MBUS_PACKING_EXTEND16:
		return width * 2;
	case SOC_MBUS_PACKING_1_5X8:
		return width * 3 / 2;
	case SOC_MBUS_PACKING_VARIABLE:
		return 0;
	}
	return -EINVAL;
}
EXPORT_SYMBOL(soc_mbus_bytes_per_line);

const struct soc_mbus_pixelfmt *soc_mbus_find_fmtdesc(
	enum v4l2_mbus_pixelcode code,
	const struct soc_mbus_lookup *lookup,
	int n)
{
	int i;

	for (i = 0; i < n; i++)
		if (lookup[i].code == code)
			return &lookup[i].fmt;

	return NULL;
}
EXPORT_SYMBOL(soc_mbus_find_fmtdesc);

const struct soc_mbus_pixelfmt *soc_mbus_get_fmtdesc(
	enum v4l2_mbus_pixelcode code)
{
	return soc_mbus_find_fmtdesc(code, mbus_fmt, ARRAY_SIZE(mbus_fmt));
}
EXPORT_SYMBOL(soc_mbus_get_fmtdesc);

static int __init soc_mbus_init(void)
{
	return 0;
}

static void __exit soc_mbus_exit(void)
{
}

module_init(soc_mbus_init);
module_exit(soc_mbus_exit);

MODULE_DESCRIPTION("soc-camera media bus interface");
MODULE_AUTHOR("Guennadi Liakhovetski <g.liakhovetski@gmx.de>");
MODULE_LICENSE("GPL v2");
