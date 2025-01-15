Basics
======

#####################
Application structure
#####################

On a fundamental level, there are 3 main parts:
   1. .. doxygenclass:: ModelWrapper
   2. .. doxygenclass:: Buffer
   3. **GUI** (MainWindow)
   
      - when rendering of a new frame is requested, graphs are updated with data from Buffer

      - after rendering is finished, displayed data is removed from the buffer


#####
Graph
#####

.. raw:: html

   <div style="overflow: auto; width: 100%;">
       <object data="_static/graphs/basic.svg" type="image/svg+xml" style="width: 100%; height: auto;"></object>
   </div>

#####
GUI elements
#####

The `MainWindow` has 4 parts:

   - **GraphGrid**: A matrix of graphs where columns represent `REFERENCE`, `SNAPSHOT` and `CURRENT` while each row corresponds to a signal type.

   - **PVGraph**: Shows p-V loops.
   - **SSGraph**: Shows stress-strain loops.
   
   - **ValueView**: Shows statistics for the previous completed beat.

.. image:: _static/graphs/GUI.png