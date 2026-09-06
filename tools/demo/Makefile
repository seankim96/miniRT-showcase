include Makefile
.PHONY: motion
motion: tools/demo/motion

tools/demo/motion: tools/demo/motion.c $(BONUS_SRCS) $(MLX_LIB) libft/libft.a
	$(CC) $(CPPFLAGS) $(CFLAGS) -Ibonus $(filter-out bonus/main.c,$(BONUS_SRCS)) $< $(LDFLAGS) $(LDLIBS) -o $@
