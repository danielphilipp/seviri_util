/******************************************************************************%
**
**    Copyright (C) 2014-2015 Greg McGarragh <mcgarragh@atm.ox.ac.uk>
**
**    This source code is licensed under the GNU General Public License (GPL),
**    Version 3.  See the file COPYING for more details.
**
**
**    17th Jul 2015: SRP updated Rad to BT coefficients for MSG-1
**                   added coefficients for MSG-3 and MSG-4
**
**
*******************************************************************************/
#include "internal.h"
#include "seviri_native_util.h"


/* MSG-1, MSG-2, MSG-3, MSG-4 */
const ushort n_satellites = 4;

/* Located in the Native MSG level 1.5 header.  Used to find the index to the
   satellite dependent constants below. */
const ushort satellite_ids[] = {321, 322, 323, 324};


/* Ref: PDF_TEN_05105_MSG_IMG_DATA, Table 1  */
const double channel_center_wavelength[SEVIRI_N_BANDS] =
     {0.635, 0.81, 1.64, 3.92, 6.25, 7.35, 8.70, 9.66, 10.80, 12.00,
      13.40, 0.75};

/* Ref: PDF_MSG_SEVIRI_RAD2REFL, Table 1 */
const double band_solar_irradiance[][SEVIRI_N_BANDS] =
{
     /* MSG-1, 321 */
     {65.2296, 73.0127, 62.3715, -999., -999., -999., -999., -999., -999.,
      -999., 78.7599},
     /* MSG-2, 322 */
     {65.2065, 73.1869, 61.9923, -999., -999., -999., -999., -999., -999.,
      -999., 79.0113},
     /* MSG-3, 323 */
     {65.5148, 73.1807, 62.0208, -999., -999., -999., -999., -999., -999.,
      -999., 78.9416},
     /* MSG-4, 324 */
     {65.2656, 73.1692, 61.9416, -999., -999., -999., -999., -999., -999.,
      -999., 79.0035}
};

/* Ref: ROSENFELD_D_2004, Page 6 */
/* Updated from The Conversion from Effective Radiances to Equivalent Brightness Temperatures, EUMETSAT 2012
   http://www.eumetsat.int/website/home/Data/Products/Calibration/MSGCalibration/index.html */

const double bt_nu_c[][SEVIRI_N_BANDS] =
{
     /* MSG-1, 321 */
     {0.0, 0.0, 0.0, 2567.330, 1598.103, 1362.081, 1149.069, 1034.343, 930.647,
      839.660, 752.387, 0.0},
     /* MSG-2, 322 */
     {0.0, 0.0, 0.0, 2568.832, 1600.548, 1360.330, 1148.620, 1035.289, 931.700,
      836.445, 751.792, 0.0},
     /* MSG-3, 323 */
     {0.0, 0.0, 0.0, 2547.771, 1595.621, 1360.377, 1148.130, 1034.715, 929.842,
      838.659, 750.653, 0.0},
     /* MSG-4, 324 */
     {0.0, 0.0, 0.0, 2555.280, 1596.080, 1361.748, 1147.433, 1034.851, 931.122,
      839.113, 748.585, 0.0}
};

const double bt_A[][SEVIRI_N_BANDS] =
{
     /* MSG-1, 321 */
     {0.0, 0.0, 0.0, 0.9956, 0.9962, 0.9991, 0.9996, 0.9999, 0.9983, 0.9988,
      0.9981, 0.0},
     /* MSG-2, 322 */
     {0.0, 0.0, 0.0, 0.9954, 0.9963, 0.9991, 0.9996, 0.9999, 0.9983, 0.9988,
      0.9981, 0.0},
     /* MSG-3, 323 */
     {0.0, 0.0, 0.0, 0.9915, 0.9960, 0.9991, 0.9996, 0.9999, 0.9983, 0.9988,
      0.9982, 0.0},
     /* MSG-4, 324 */
     {0.0, 0.0, 0.0, 0.9916, 0.9959, 0.9990, 0.9996, 0.9998, 0.9983, 0.9988,
      0.9981, 0.0}
};

const double bt_B[][SEVIRI_N_BANDS] =
{
     /* MSG-1, 321 */
     {0.0, 0.0, 0.0, 3.410, 2.218, 0.478, 0.179, 0.060, 0.625, 0.397,
      0.578, 0.0},
     /* MSG-2, 322 */
     {0.0, 0.0, 0.0, 3.438, 2.185, 0.470, 0.179, 0.056, 0.640, 0.408,
      0.561, 0.0},
     /* MSG-3, 323 */
     {0.0, 0.0, 0.0, 2.9002, 2.0337, 0.4340, 0.1714, 0.0527, 0.6084, 0.3882,
      0.5390, 0.0},
     /* MSG-4, 324 */
     {0.0, 0.0, 0.0, 2.9438, 2.0780, 0.4929, 0.1731, 0.0597, 0.6256, 0.4002,
      0.5635, 0.0}
};

/* Ref: PDF_CGMS_LRIT_HRIT_2_6, Page 36 */
const struct nav_scaling_factors nav_scaling_factors_vir =
     {-781648343., -781648343., 1856., 1856.};
const struct nav_scaling_factors nav_scaling_factors_hrv =
     {-2344944937., -2344944937., 5566., 5566};
