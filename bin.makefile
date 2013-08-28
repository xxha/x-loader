
post_build :: x-loader/$(MODE_DIR)/x-loader-fat16.bin

x-loader/$(MODE_DIR)/x-loader-fat16.bin: x-loader/$(MODE_DIR)/x-loader.elf
	@echo "Converting $< to $@"
	@$(TOOL_PATH)ddump -Ruv $<
	@$(PRJ_ROOT_DIR)/bin/mkfatboot $<.bin > $@
	@rm $<.bin
