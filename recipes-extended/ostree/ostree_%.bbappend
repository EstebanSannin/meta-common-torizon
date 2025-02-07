FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

inherit bash-completion

SRC_URI:append = " \
    file://0001-ostree-grub-generator-allow-adding-custom-scripts-to.patch \
    file://0001-update-default-grub-cfg-header.patch \
    file://0002-Add-support-for-the-fdtfile-variable-in-uEnv.txt.patch \
    file://0003-ostree-fetcher-curl-handle-non-404-errors-as-G_IO_ER.patch \
    file://0004-ostree-fetcher-curl-set-max-parallel-connections.patch \
    file://ostree-pending-reboot.service \
    file://ostree-pending-reboot.path \
"

# Disable PTEST for ostree as it requires options that are not enabled when
# building with meta-updater
PTEST_ENABLED = "0"

# gpgme is not required, and it brings GPLv3 dependencies
PACKAGECONFIG:remove = "gpgme"

SYSTEMD_SERVICE:${PN} += "ostree-pending-reboot.path ostree-pending-reboot.service"

def is_ti(d):
    overrides = d.getVar('OVERRIDES')
    if not overrides:
        return False
    overrides = overrides.split(':')
    if 'ti-soc' in overrides:
        return True
    else:
        return False

def get_deps(d):
    # NOTE: beagleplay is TI but does not use the Toradex BSP
    if is_ti(d) and ('beagleplay' not in d.getVar('MACHINE')) :  # TI
        return 'u-boot-toradex-ti' if d.getVar('PREFERRED_PROVIDER_u-boot') else ''
    else:  # NXP/x86 generic/QEMU
        return 'u-boot-default-script' if d.getVar('PREFERRED_PROVIDER_u-boot-default-script') else ''

def get_rdeps(d):
    if is_ti(d):  # TI
        return 'ostree-uboot-env' if d.getVar('PREFERRED_PROVIDER_u-boot') else ''
    else:  # NXP/x86 generic/QEMU
        return 'ostree-uboot-env' if d.getVar('PREFERRED_PROVIDER_u-boot-default-script') else ''

DEPENDS:append:class-target = " ${@get_deps(d)}"
RDEPENDS:${PN}:append:class-target = " ${@get_rdeps(d)}"

do_install:append () {
    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${WORKDIR}/ostree-pending-reboot.service ${D}${systemd_system_unitdir}
    install -m 0644 ${WORKDIR}/ostree-pending-reboot.path ${D}${systemd_system_unitdir}

    install -d ${D}${sysconfdir}/ostree.d
}
