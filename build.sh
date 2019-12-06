#!/bin/bash -e
source /opt/ros/kinetic/setup.bash
rosdep install --from-paths src --ignore-src -r -y
catkin_make -DCATKIN_WHITELIST_PACKAGES="navigation"
catkin_make -DCATKIN_WHITELIST_PACKAGES="" -DCATKIN_BLACKLIST_PACKAGES="move_forward"
catkin_make -DCATKIN_WHITELIST_PACKAGES="" -DCATKIN_BLACKLIST_PACKAGES=""
