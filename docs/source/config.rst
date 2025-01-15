Configuration
=============

The application is designed with a high degree of flexibility, 
allowing users to tailor its behavior and appearance to suit their needs. 

Configuration is stored in `config.json <configfile.html>`_ which should be located alongside the binary file.
It is read at application launch.

Key configuration options include:

    - **Frames Per Second (FPS)**: Users can define the desired update frequency for rendering and data visualization.

    - **Buffer size**: Defines the number of time-related datapoints are kept in buffer. 
        
        .. note::
            For slower systems this value shoud be increased.

    - **Padding**: Defines the extra space added to graphs when signals are autoscaled. In percentage.
    - **Model configuration**: Select which solver to use.

        - **Exported signals**: Select which signals the model exports to the buffer.
        - **Parameter Adjustments**: Choose which model parameters can be directly modified through the GUI.
    
    - **Customization of Signals**: Configure attributes such as colors and units for signals.

.. toctree::
    :hidden:

    configfile
    datacontainers
    modelconf
    guiconf

