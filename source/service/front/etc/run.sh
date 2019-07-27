#!/bin/sh
DIR="$( cd "$(dirname "$0")" ; pwd -P )"
$DIR/service.front `hostname -I | cut -f1 -d' '`