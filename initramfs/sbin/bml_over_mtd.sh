#!/sbin/busybox sh
#
# bml_over_mtd.sh
# Take care of bad blocks while flashing kernel image to boot partition
#

PARTITION=$1
PARTITION_START_BLOCK=$2
RESERVOIRPARTITION=$3
RESERVOIR_START_BLOCK=$4
IMAGE=$5

# remove old log
rm -rf /sdcard/bml_over_mtd.log

# everything is logged into /sdcard/bml_over_mtd.log
exec >> /sdcard/bml_over_mtd.log 2>&1

set -x
export PATH=/:/sbin:/system/xbin:/system/bin:$PATH

busybox cat <<EOF
########################################################################################
#
# Flashing boot image with bml_over_mtd on `busybox date`
#
########################################################################################
EOF

# scan boot partition for bad blocks
/sbin/bml_over_mtd scan $PARTITION
status=$?
 
echo "Running bml_over_mtd..."
/sbin/bml_over_mtd flash $PARTITION $PARTITION_START_BLOCK $RESERVOIRPARTITION $RESERVOIR_START_BLOCK $IMAGE 

exit