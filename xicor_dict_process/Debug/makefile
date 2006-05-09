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

all: libxicor_dict_process.so

dependents:
	-cd /home/burivuh/workspace/xicor/xicor_base/Debug && $(MAKE) all

libxicor_dict_process.so: $(OBJS) /home/burivuh/workspace/xicor/xicor_base/Debug/libxicor_base.so
	@echo 'Building target: $@'
	g++ -shared -o $@ $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building: $@'

clean:
	-$(RM) $(OBJS) $(DEPS) libxicor_dict_process.so

.PHONY: all clean dependents
/home/burivuh/workspace/xicor/xicor_base/Debug/libxicor_base.so:

-include $(ROOT)/makefile.targets
