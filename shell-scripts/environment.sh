#bin/bash

SESSION_NAME=botsession

if [ -z "$SESSION_ENV" ]
then
    echo ""
    echo "Please set SESSION_ENV to either laptop or nano and run again."
    echo ""
    exit 1
else
    echo "Using [$SESSION_ENV] for configs."

    if [[ "$SESSION_ENV" = "nano" ]]
    then
        FUSE_CONFIG_FILE_PATH="config/nano.yml"
        VPM_CONFIG_FILE_PATH="config/vpm-nano.yml"
    fi

    if [[ "$SESSION_ENV" = "laptop" ]]
    then
        FUSE_CONFIG_FILE_PATH="config/config.yml"
        VPM_CONFIG_FILE_PATH="config/vpm.yml"
    fi

    if [ -z "$FUSE_CONFIG_FILE_PATH" ]
    then
        echo ""
        echo "UNKNOWN SESSION_ENV [$SESSION_ENV]."
        echo ""
        exit 2
    else
        echo "Using fuse configuration for [$SESSION_ENV]=[$FUSE_CONFIG_FILE_PATH]"
        echo "Using vpm configuration for [$SESSION_ENV]=[$VPM_CONFIG_FILE_PATH]"
    fi

fi