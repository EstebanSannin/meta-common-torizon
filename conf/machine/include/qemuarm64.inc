UBOOT_MACHINE = "qemu_arm64_defconfig"
UBOOT_ENTRYPOINT = "0x40080000"

WKS_FILE_DEPENDS:remove = "tezi-metadata virtual/dtb"
WKS_FILE:sota:qemuarm64 = "torizon-sota.wks"

CORE_IMAGE_BASE_INSTALL:append = "resize-helper"

OSTREE_KERNEL_ARGS:qemuarm64 = "quiet logo.nologo plymouth.ignore-serial-consoles splash console=ttyAMA0 root=LABEL=otaroot rootfstype=ext4"
OSTREE_DEPLOY_DEVICETREE:qemuarm64 = "0"

QB_MACHINE = "-machine virt"
QB_DRIVE_TYPE = "/dev/vda"
QB_DEFAULT_FSTYPE = "wic"
QB_MEM:qemuarm64 = "-m 1057"
QB_OPT_APPEND:qemuarm64 = "-device qemu-xhci -device usb-tablet -device usb-kbd -no-acpi -bios ${DEPLOY_DIR_IMAGE}/u-boot.bin -d unimp -semihosting-config enable=on,target=native"

IMAGE_FSTYPES_REMOVE = "tar.bz2 ext4 teziimg"
IMAGE_FSTYPES:append = " wic"

hostname:pn-base-files = "${MACHINE}"
CORE_IMAGE_BASE_INSTALL:remove = "set-hostname"

PACKAGECONFIG:append:pn-qemu-system-native = " sdl"
PACKAGECONFIG:append:pn-nativesdk-qemu = " sdl"

PREFERRED_PROVIDER_virtual/dtb = ""
PREFERRED_RPROVIDER_network-configuration:qemuarm64 = "networkd-static-conf"

PREFERRED_PROVIDER_virtual/bootloader = "u-boot"
PREFERRED_PROVIDER_virtual/kernel:qemuarm64 = "linux-yocto"
PREFERRED_PROVIDER_virtual/kernel:qemuarm64:preempt-rt = "linux-yocto-rt"

PREFERRED_PROVIDER_u-boot-default-script:qemuarm64 = "u-boot-distro-boot"

OSTREE_KERNEL_ARGS:sota:append:qemuarm64 = "console=ttyAMA0 root=LABEL=otaroot rootfstype=ext4 logo.nologo vt.global_cursor_default=0 plymouth.ignore-serial-consoles splash fbcon=map:10 "
