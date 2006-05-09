################################################################################
# Automatically-generated file. Do not edit!
################################################################################

ROOT := ..

-include $(ROOT)/makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include $(SUBDIRS:%=%/subdir.mk)
-include objects.mk
-include $(DEPS)
-include $(ROOT)/makefile.defs

all: xicor_core

dependents:
	-cd /home/burivuh/workspace/xicor/xicor_base/Debug && $(MAKE) all

xicor_core: $(OBJS) /home/burivuh/workspace/xicor/xicor_base/Debug/libxicor_base.so
	@echo 'Building target: $@'
	g++ -L./../../xicor_base/Debug/ -o $@ $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building: $@'

clean:
	-$(RM) $(OBJS) $(DEPS) xicor_core

.PHONY: all clean dependents
/home/burivuh/workspace/xicor/xicor_base/Debug/libxicor_base.so:

-include $(ROOT)/makefile.targets
