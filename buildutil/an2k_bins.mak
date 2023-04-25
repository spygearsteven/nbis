#*******************************************************************************
#
# License: 
# This software was developed at the National Institute of Standards and 
# Technology (NIST) by employees of the Federal Government in the course 
# of their official duties. Pursuant to title 17 Section 105 of the 
# United States Code, this software is not subject to copyright protection 
# and is in the public domain. NIST assumes no responsibility  whatsoever for 
# its use by other parties, and makes no guarantees, expressed or implied, 
# about its quality, reliability, or any other characteristic. 
#
# This software has been determined to be outside the scope of the EAR
# (see Part 734.3 of the EAR for exact details) as it has been created solely
# by employees of the U.S. Government; it is freely distributed with no
# licensing requirements; and it is considered public domain.  Therefore,
# it is permissible to distribute this software as a free download from the
# internet.
#
# Disclaimer: 
# This software was developed to promote biometric standards and biometric
# technology testing for the Federal Government in accordance with the USA
# PATRIOT Act and the Enhanced Border Security and Visa Entry Reform Act.
# Specific hardware and software products identified in this software were used
# in order to perform the software development.  In no case does such
# identification imply recommendation or endorsement by the National Institute
# of Standards and Technology, nor does it imply that the products and equipment
# identified are necessarily the best available for the purpose.  
#
#*******************************************************************************

# Filename:             an2k_bins.mak
# Integrators:          Kenneth Ko
# Organization:         NIST/ITL
# Host System:          GNU GCC/GMAKE GENERIC (UNIX)
# Date Created:         08/20/2006
# Date Updated:         01/31/2008 (Kenneth Ko)
# Date Updated:         09/03/2008 (Kenneth Ko)
#
# ******************************************************************************
#
# Makefile to loop through an2k binary directories and call the next
# level Makefile.
#
# ******************************************************************************
bins:
	@( \
		for program in $(PROGRAMS); do \
			if [ "$$program" = "dpyan2k" -a $(X11_FLAG) -eq 1 ]; then \
				echo "Start: Compiling $$program binary...."; \
				(cd $(DIR_SRC_BIN)/$$program && $(MAKE) -f Makefile.X11 it) || exit 1; \
				echo "End: Compiling $$program binary."; \
			elif [ "$$program" != "dpyan2k" ]; then \
				echo "Start: Compiling $$program binary...."; \
				(cd $(DIR_SRC_BIN)/$$program && $(MAKE) it) || exit 1; \
				echo "End: Compiling $$program binary."; \
			fi; \
		done;\
	);
#
config:
	@( \
		for program in $(PROGRAMS); do \
			if [ "$$program" = "dpyan2k" -a $(X11_FLAG) -eq 1 ]; then \
				(cd $(DIR_SRC_BIN)/$$program && $(MAKE) -f Makefile.X11 config) || exit 1; \
			elif [ "$$program" != "dpyan2k" ]; then \
				(cd $(DIR_SRC_BIN)/$$program && $(MAKE) config) || exit 1; \
			fi; \
		done;\
	);
#
install:
	@( \
		for program in $(PROGRAMS); do \
			if [ "$$program" = "dpyan2k" -a $(X11_FLAG) -eq 1 ]; then \
				(cd $(DIR_SRC_BIN)/$$program && $(MAKE) -f Makefile.X11 install) || exit 1; \
			elif [ "$$program" != "dpyan2k" ]; then \
				(cd $(DIR_SRC_BIN)/$$program && $(MAKE) install) || exit 1; \
			fi; \
		done;\
	);
#
clean:
	@( \
		for program in $(PROGRAMS); do \
			if [ "$$program" = "dpyan2k" -a $(X11_FLAG) -eq 1 ]; then \
				(cd $(DIR_SRC_BIN)/$$program && $(MAKE) -f Makefile.X11 clean) || exit 1; \
			elif [ "$$program" != "dpyan2k" ]; then \
				(cd $(DIR_SRC_BIN)/$$program && $(MAKE) clean) || exit 1; \
			fi; \
		done;\
	);
#
catalog:
	@( \
		for program in $(PROGRAMS); do \
			if [ "$$program" = "dpyan2k" -a $(X11_FLAG) -eq 1 ]; then \
				(cd $(DIR_SRC_BIN)/$$program && $(MAKE) -f Makefile.X11 catalog) || exit 1; \
			elif [ "$$program" != "dpyan2k" ]; then \
				(cd $(DIR_SRC_BIN)/$$program && $(MAKE) catalog) || exit 1; \
			fi;\
		done;\
	);
#
