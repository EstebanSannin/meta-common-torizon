SUMMARY = "TorizonCore - experimental image using Podman"
DESCRIPTION = "TorizonCore Linux experimental image based on production image \
using Podman container engine."

require torizon-core-common.inc

IMAGE_VARIANT = "Podman"

CORE_IMAGE_BASE_INSTALL:append = " \
    podman \
    podman-compose \
    fuse-overlayfs \
"
