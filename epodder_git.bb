DESCRIPTION = "A mp3 player and podcasting client based on efl libraries"
HOMEPAGE = "http://github.com/cgerum/epodder"
AUTHOR = "Christoph Gerum <christoph@gerum.de>"
LICENSE  = "GPL"
DEPENDS = "elementary gstreamer libmrss"
SECTION = "x11/application"
SRCREV ?= "${AUTOREV}"
PV = "0.0.1+r${SRCREV}"
PR = "r0"


SRC_URI = "git://github.com/cgerum/epodder.git;protocol=git;branch=master"
S = "${WORKDIR}/git"


FILES_${PN} += "${prefix}/share/pixmaps"
FILES_${PN} += "${prefix}/share/applications"

inherit autotools pkgconfig 