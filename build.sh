#!/bin/bash -e
rosdep install --from-paths src --ignore-src -r -y
catkin_make --only-pkg-with-deps navigation
catkin_make -DCATKIN_BLACKLIST_PACKAGES="move_forward"
catkin_make
