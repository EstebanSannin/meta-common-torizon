
WKS_FILE:intel-corei7-64:sota = "efiimage-sota.wks"
WKS_FILE_DEPENDS:remove = "tezi-metadata virtual/dtb"

CORE_IMAGE_BASE_INSTALL:append = "resize-helper docker-binfmt"

OSTREE_KERNEL_ARGS:sota:append:intel-corei7-64 = "console=ttyS0,115200 root=LABEL=otaroot rootfstype=ext4 quiet logo.nologo vt.global_cursor_default=0 plymouth.ignore-serial-consoles splash fbcon=map:10 "
OSTREE_BOOTLOADER:intel-corei7-64 = "grub"
OSTREE_DEPLOY_DEVICETREE:intel-corei7-64 = "0"
EFI_PROVIDER:intel-corei7-64 = "grub-efi"
SOTA_CLIENT_FEATURES:remove = "ubootenv"
UBOOT_BINARY_OTA_IGNORE:intel-corei7-64 = "1"

IMAGE_FSTYPES_REMOVE = "hddimg teziimg"
IMAGE_FSTYPES:append = " wic.vmdk wic.vdi"

hostname:pn-base-files = "torizon-x86"
CORE_IMAGE_BASE_INSTALL:remove = "set-hostname"

PREFERRED_PROVIDER_u-boot-default-script = ""
PREFERRED_PROVIDER_virtual/dtb = ""

PREFERRED_PROVIDER_virtual/kernel = "linux-intel"
PREFERRED_VERSION_linux-intel = "5.10.%"

IMAGE_INSTALL:remove = " minnowboard-efi-startup"
LINUX_VERSION_EXTENSION ?= "-torizon-${LINUX_KERNEL_TYPE}"
