`config.json`
=============

The configuration file for the application defines various settings and parameters. Below is the structure of the configuration file, along with examples.

Top-Level Structure
-------------------

- **ModelWrapper**: Defines simulation-related parameters, including the solver and signals to export.

    - **solver** 
    - **export_signals**: Signals appended to buffer after every solver timestep

        - **name**: Used as a key when specifying which signals are to be displayed on a graph. See `PVGraph`, `SSGraph`, `GraphGrid`.
        - **path**: Path to a speficified CircAdapt signal. See CircAdapt documentation for details.
        - **type**: Specifies the type of the signal. Needed for correct conversion of values between the model and UI. There are several predefined types, see :ref:`datacontainers` for more information.

        .. note::
            Some additional signals are exported to buffer. They are not specified
            in the user config file because they are needed for certain calculations.

            See `ModelWrapper::setupAdditionalSignals`

    - **parameters**: Parameters which can be changed from the GUI.

        - **name**: Used as a key at defining GUI elements for parameter modification. See `ModelParameters`.
        - **path**: Path to a speficified CircAdapt parameter. See CircAdapt documentation for details.
        - **type**: Specifies the type of parameter. Needed for correct conversion of values between the model and UI. There are several predefined types, see :ref:`datacontainers` for more information.

- **GUI**: 

    - **framerate**: How many frames are displayed per second.
    - **buffersize**: Number of time-related datapoints kept in buffer.
    - **padding**: Extra space around the signals when using autoscale function. In percent with respect to graph coordinates.
- **PVGraph**: Configures pressure-volume graphs, including titles and signal mappings.

    - **title**

    - **xLabel**
    - **yLabel**

    - **Signals**: Array of signals to be displayed on this graph.

        - **displayName**: Name of the signal, visible in tooltip on hover or right-click menu.

        - **xVar**: Key of signal used for x-value.
        - **yVar**: Key of signal used for y-value.
        - **isVisible**: Is it shown when starting the application.
        - **unit**

        - **color**

- **SSGraph**: Configures stress-strain graphs, including titles and signal mappings.

    - **title**

    - **xLabel**
    - **yLabel**

        - **displayName**: Name of the signal, visible in tooltip on hover or right-click menu.

        - **xVar**: Key of signal used for x-value.
        - **yVar**: Key of signal used for y-value.
        - **isVisible**: Is it shown when starting the application.
        - **unit**

        - **color**

- **GraphGrid**: Defines signals grouped by type. Each type regards one row. Each row has 3 columns: `REFERENCE`, `SNAPSHOT`, `CURRENT`.

    Row types are:

    .. doxygenenum:: GraphGrid::RowType

    In `config.json`, each row specifier takes a list of signals to be displayed in that row. Keys for defining signals are:

        - **displayName**: Name of the signal, visible in tooltip on hover or right-click menu.

        - **name**: Key of the signal corresponding to one of `export_signals`.
        - **isVisible**: Is it shown when starting the application.
        - **unit**
        - **color**

        - **inMainMenu**: Indicates whether the signal is displayed directly in the main menu upon right-click or nested within the `More` submenu.

- **ValueView**: Specifies metrics which are shown in the table (eg. CO, mLAP, ...).
    
    A list of objects with keys:

        - **name**: Corresponds to an element of m_beatStats from Buffer class. See Buffer.
        
        - **unit**



Example Structure
-----------------

.. code-block:: json

    {
        "ModelWrapper": {
            "solver": "forward_euler",
            "export_signals": [
                {
                    "name": "pLa",
                    "path": "Model.Peri.La.p",
                    "type": "pressure"
                },
                {
                    "name": "pRa",
                    "path": "Model.Peri.Ra.p",
                    "type": "pressure"
                },
                ...
            ],
            "parameters": [
                {
                    "name": "Left atrial contractility",
                    "path": "Model.Peri.La.Sf_act",
                    "type": "percentage"
                },
                ...
            ]
        },
        "GUI": {
            "framerate": 60,
            "buffersize": 50,
            "padding": 0.05
        },
        "PVGraph": {
            "title": "Pressure-volume loops",
            "xLabel": "Volume [mL]",
            "yLabel": "Pressure [mmHg]",
            "Signals": [
                {
                    "displayName": "Left atrium",
                    "xVar": "VLa",
                    "yVar": "pLa",
                    "isVisible": false,
                    "color": "#FB9A99"
                },
                ...
            ]
        },
        "SSGraph": {
            "title": "Stress-strain loops",
            "xLabel": "Strain [%]",
            "yLabel": "Stress [kPa]",
            "Signals": [
                {
                    "displayName": "Left atrium",
                    "xVar": "strain_La",
                    "yVar": "Sf_La",
                    "isVisible": false,
                    "color": "#FB9A99"
                },
                ...
            ]
        },
        "GraphGrid": {
            "PRESSURE": [
                {
                    "name": "pLa",
                    "displayName": "Left atrium",
                    "isVisible": false,
                    "unit": "mmHg",
                    "color": "#FB9A99",
                    "inMainMenu": true
                },
                ...
            ],
            "VOLUME": [
                ...
            ],
            ...
        },
        "ValueView": [
            {
                "name": "CO",
                "unit": "L/min"
            },
            {
                "name": "mLAP",
                "unit": "mmHg"
            },
            ...
        ]
    }
