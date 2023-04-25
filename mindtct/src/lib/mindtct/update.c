/*******************************************************************************

License: 
This software and/or related materials was developed at the National Institute
of Standards and Technology (NIST) by employees of the Federal Government
in the course of their official duties. Pursuant to title 17 Section 105
of the United States Code, this software is not subject to copyright
protection and is in the public domain. 

This software and/or related materials have been determined to be not subject
to the EAR (see Part 734.3 of the EAR for exact details) because it is
a publicly available technology and software, and is freely distributed
to any interested party with no licensing requirements.  Therefore, it is 
permissible to distribute this software as a free download from the internet.

Disclaimer: 
This software and/or related materials was developed to promote biometric
standards and biometric technology testing for the Federal Government
in accordance with the USA PATRIOT Act and the Enhanced Border Security
and Visa Entry Reform Act. Specific hardware and software products identified
in this software were used in order to perform the software development.
In no case does such identification imply recommendation or endorsement
by the National Institute of Standards and Technology, nor does it imply that
the products and equipment identified are necessarily the best available
for the purpose.

This software and/or related materials are provided "AS-IS" without warranty
of any kind including NO WARRANTY OF PERFORMANCE, MERCHANTABILITY,
NO WARRANTY OF NON-INFRINGEMENT OF ANY 3RD PARTY INTELLECTUAL PROPERTY
or FITNESS FOR A PARTICULAR PURPOSE or for any purpose whatsoever, for the
licensed product, however used. In no event shall NIST be liable for any
damages and/or costs, including but not limited to incidental or consequential
damages of any kind, including economic damage or injury to property and lost
profits, regardless of whether NIST shall be advised, have reason to know,
or in fact shall know of the possibility.

By using this software, you agree to bear all risk relating to quality,
use and performance of the software and/or related materials.  You agree
to hold the Government harmless from any claim arising from your use
of the software.

*******************************************************************************/


/***********************************************************************
      LIBRARY: LFS - NIST Latent Fingerprint System

      FILE:    UPDATE.C
      AUTHOR:  Michael D. Garris
      DATE:    09/14/2004
      UPDATED: 01/31/2008 by Kenneth Ko
      UPDATED: 09/04/2008 by Kenneth Ko

      Routines responsible for taking LFS results and updating
      structures such as ANSI/NIST.

***********************************************************************
               ROUTINES:
                        update_ANSI_NIST_lfs_results()

***********************************************************************/

#include <stdio.h>
#include <lfs.h>
#include <an2k.h>


/*************************************************************************
**************************************************************************
#cat: update_ANSI_NIST_lfs_results - Updates an ANSI/NIST structure by creating
#cat:             and inserting a new Type-9 record containing the detected
#cat:             minutiae and a Type-13 or 14 record containing the
#cat:             resulting binarized image from LFS.

   Input:
      ansi_nist - ANSI/NIST structure to be modified
      minutiae  - structure containing the detected minutiae
      idata     - binarized fingerprint image data
      iw        - width (in pixels) of the binarized image
      ih        - height (in pixels) of the binarized image
      id        - pixel depth (in bits) of the binarized image
      ppmm      - the scan resolution (in pixels/mm) of the binarized image
      img_idc   - the image record's IDC
      img_imp   - the image record's impression type (IMP)
   Output:
      ansi_nist - the modified ANSI/NIST structure
   Return Code:
      Zero     - successful completion
      Negative - system error
**************************************************************************/
int update_ANSI_NIST_lfs_results(ANSI_NIST *ansi_nist, MINUTIAE *minutiae,
                     unsigned char *idata, const int iw, const int ih,
                     const int id, const double ppmm, const int img_idc,
                     const int img_imp)
{
   int ret, ilen;
   RECORD *type_9, *imgrecord;

   if(minutiae->num > 0){
      /* Convert Minutiae list to Standard Type-9 Record. */
      if((ret = minutiae2type_9(&type_9, img_idc, minutiae, iw, ih, ppmm))){
         return(ret);
      }

      /* Insert Type-9 record at end of input ANSI/NIST file. */
      if((ret = insert_ANSI_NIST_record_frmem(ansi_nist->num_records,
                                             type_9, ansi_nist))){
         free_ANSI_NIST_record(type_9);
         return(ret);
      }
   }


   /* Convert image pixmap to a tagged field image record based */
   /* on the Impression Type of the input image. */
   switch(id){
      case 1:
         ilen = (iw>>3) * ih;
         break;
      case 8:
         ilen = iw * ih;
         break;
      case 24:
         ilen = iw * ih * 3;
         break;
      default:
         fprintf(stderr, "ERROR : update_ANSI_NIST_lfs_results : ");
         fprintf(stderr, "image pixel depth = %d != {1,8,24}\n", id);
         return(-2);
   }
   
   if((ret = fingerprint2tagged_field_image(&imgrecord, idata, ilen,
                                           iw, ih, id, ppmm,
                                           COMP_NONE, img_idc,
                                           img_imp, LFS_VERSION_STR))){
      return(ret);
   }

   /* Insert Binary Image record at end of input ANSI/NIST file. */
   if((ret = insert_ANSI_NIST_record_frmem(ansi_nist->num_records,
                                          imgrecord, ansi_nist))){
      free_ANSI_NIST_record(imgrecord);
      return(ret);
   }

   /* Return normally. */
   return(0);
}
