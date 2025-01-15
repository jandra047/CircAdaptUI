.. _datacontainers:

==============
Data Container
==============

The `DataContainer` class serves as a bridge between the underlying model and the user interface, providing automated value conversion and type-safe data handling. This document outlines the structure and responsibilities of the class.

Classes
-------

.. doxygenclass:: DataContainer
    :members:
    :private-members:
    :protected-members:
    :undoc-members:

.. doxygenclass:: DataContainerFactory

Subclasses
----------

.. doxygenclass:: PressureContainer
.. doxygenclass:: StressContainer
.. doxygenclass:: VolumeContainer
.. doxygenclass:: FlowContainer
.. doxygenclass:: FlowVelocityContainer
    :members:
.. doxygenclass:: HRContainer
.. doxygenclass:: COContainer
.. doxygenclass:: BoolContainer
.. doxygenclass:: MilliSecondsContainer
.. doxygenclass:: AreaContainer
.. doxygenclass:: DiameterContainer
.. doxygenclass:: ShuntContainer
.. doxygenclass:: PercentageCoeffContainer
.. doxygenclass:: PercentageContainer
.. doxygenclass:: CoefficientContainer
.. doxygenclass:: WallStrainContainer
.. doxygenclass:: WallMSContainer
.. doxygenclass:: WallCoeffContainer
.. doxygenclass:: WallPercentageContainer
.. doxygenclass:: ConcentrationContainer

Usage
-----

Each parameter manipulated from the UI or signal displayed has to be wrapped in one of `DataContainer` subclasses.

**Example 1**: Changing a model parameter from the UI
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp
    
    Buffer* buffer = new Buffer();
    ModelWrapper* wrapper = new ModelWrapper(buffer);
    // Wrapper configuration...

    QJsonObject config;
    config["name"] = "Left atrial contractility";
    config["path"] = "Model.Peri.La.Sf_act";
    config["type"] = "percentage";
    config["default"] = wrapper.get_double("Model.Peri.La.Sf_act");
   
    DataContainer* container = DataContainerFactory::createContainer(config, wrapper);

    container->updateParam(90); // Model parameter is updated with 90/100 * defaultValue
