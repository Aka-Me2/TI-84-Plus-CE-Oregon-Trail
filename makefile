# -------------------------
# makefile options
# -------------------------
NAME = ORGTRAIL
DESCRIPTION = "A remake of the Oregon Trail(1971)"
COMPRESSED = YES
COMPRESSED_MODE = zx0
ARCHIVED = YES

#compiler configuration
CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# -------------------------
include $(shell cedev-config --makefile)