#!/bin/bash
#Copie right Rafik BOUAICHA 
#Backup Script
#This script performs full, incremental, and differential backups using rsync.
#Usage:
#To backup: sudo ./backup_script.sh <source_path> <backup_type>
#To restore: sudo ./backup_script.sh restore <backup_type> <restore_date> <restore_path>

# Destination path
DESTINATION="/etc/backup"

# Create backup directories if they don't exist
mkdir -p "$DESTINATION/full" "$DESTINATION/incremental" "$DESTINATION/differential" || { echo "Failed to create backup directories"; exit 1; }

# Function for full backup
full_backup() {
    local source=$1
    local date=$2
    rsync -a --delete "$source/" "$DESTINATION/full/full_backup_$date/" || { echo "Full backup failed"; exit 1; }
    echo "Full backup completed: $DESTINATION/full/full_backup_$date/"
    rsync -a "$DESTINATION/full/full_backup_$date/" "$DESTINATION/full/latest_full_backup/" || { echo "Failed to update latest full backup"; exit 1; }
    echo "$(date): Full backup completed: $DESTINATION/full/full_backup_$date/" >> "$DESTINATION/backup.log"
}

# Function for incremental backup
incremental_backup() {
    local source=$1
    local date=$2
    rsync -a --link-dest="$DESTINATION/full/latest_full_backup/" "$source/" "$DESTINATION/incremental/incremental_backup_$date/" || { echo "Incremental backup failed"; exit 1; }
    echo "Incremental backup completed: $DESTINATION/incremental/incremental_backup_$date/"
    echo "$(date): Incremental backup completed: $DESTINATION/incremental/incremental_backup_$date/" >> "$DESTINATION/backup.log"
}

# Function for differential backup
differential_backup() {
    local source=$1
    local date=$2
    rsync -a --compare-dest="$DESTINATION/full/latest_full_backup/" "$source/" "$DESTINATION/differential/differential_backup_$date/" || { echo "Differential backup failed"; exit 1; }
    echo "Differential backup completed: $DESTINATION/differential/differential_backup_$date/"
    echo "$(date): Differential backup completed: $DESTINATION/differential/differential_backup_$date/" >> "$DESTINATION/backup.log"
}

# Function for restoration
restore_backup() {
    local backup_type=$1
    local restore_date=$2
    local restore_path=$3

    case $backup_type in
        1)
            rsync -a "$DESTINATION/full/full_backup_$restore_date/" "$restore_path/" || { echo "Full restore failed"; exit 1; }
            echo "Full restore completed from: $DESTINATION/full/full_backup_$restore_date/ to: $restore_path/"
            ;;
        2)
            rsync -a --link-dest="$DESTINATION/full/latest_full_backup/" "$DESTINATION/incremental/incremental_backup_$restore_date/" "$restore_path/" || { echo "Incremental restore failed"; exit 1; }
            echo "Incremental restore completed from: $DESTINATION/incremental/incremental_backup_$restore_date/ to: $restore_path/"
            ;;
        3)
            rsync -a --compare-dest="$DESTINATION/full/latest_full_backup/" "$DESTINATION/differential/differential_backup_$restore_date/" "$restore_path/" || { echo "Differential restore failed"; exit 1; }
            echo "Differential restore completed from: $DESTINATION/differential/differential_backup_$restore_date/ to: $restore_path/"
            ;;
        *)
            echo "Invalid backup type for restoration. Please enter 1 for Full, 2 for Incremental, or 3 for Differential."
            exit 1
            ;;
    esac
}

# Check if the correct number of arguments is provided
if [ "$1" == "restore" ]; then
    if [ $# -ne 4 ]; then
        echo "Usage: $0 restore <backup_type> <restore_date> <restore_path>"
        echo "Backup types for restore: 1 = Full, 2 = Incremental, 3 = Differential"
        exit 1
    fi
    BACKUP_TYPE=$2
    RESTORE_DATE=$3
    RESTORE_PATH=$4
    restore_backup "$BACKUP_TYPE" "$RESTORE_DATE" "$RESTORE_PATH"
    exit 0
fi

# Backup functionality
if [ $# -ne 2 ]; then
    echo "Usage: $0 <source_path> <backup_type>"
    echo "Backup types: 1 = Full, 2 = Incremental, 3 = Differential"
    exit 1
fi

SOURCE_PATH=$1
BACKUP_TYPE=$2

# Check if the source path exists
if [ ! -d "$SOURCE_PATH" ]; then
    echo "Error: Source path $SOURCE_PATH does not exist."
    exit 1
fi

# Get current date for unique backup naming
DATE=$(date +'%Y-%m-%d_%H-%M-%S')

# Perform backup based on type
case $BACKUP_TYPE in
    1)
        full_backup "$SOURCE_PATH" "$DATE"
        ;;
    2)
        incremental_backup "$SOURCE_PATH" "$DATE"
        ;;
    3)
        differential_backup "$SOURCE_PATH" "$DATE"
        ;;
    *)
        echo "Invalid backup type. Please enter 1 for Full, 2 for Incremental, or 3 for Differential."
        exit 1
        ;;
esac