# Basics of IFC file syntax needed for displaying water pipes

## Header
Basic information
```
ISO-10303-21;
HEADER;
FILE_DESCRIPTION(('ViewDefinition [CoordinationView]'), '2;1');
FILE_NAME('cylinder.ifc', '2017-11-07T15:20:37', (''), (''), 'IfcOpenShell-0.5.0-dev', 'IfcOpenShell-0.5.0-dev', '');
FILE_SCHEMA(('IFC2X3'));
ENDSEC;
```

## Project metadata
```
DATA;
#1=IFCPERSON($, $, '', $, $, $, $, $);
#2=IFCORGANIZATION($, '', $, $, $);
#3=IFCPERSONANDORGANIZATION(#1, #2, $);
#4=IFCAPPLICATION(#2, '0.5.0-dev', 'IfcOpenShell-0.5.0-dev', '');
#5=IFCOWNERHISTORY(#3, #4, $, .ADDED., $, #3, #4, 1510068037.0321496);
```


## Let's create cylinder

### Base
At first, we need to define base of the cylinder, which is simple circle. The circle will be created in 2D space, so we need to define it's position position with **IFCCARTESIANPOINT** and direction of X-axis with **IFCDIRECTION**. This coordinates doesn't matter for the future cylinder placement. The circle is then simply created with **IFCCIRCLEPROFILEDEF**. The fourth parameter is the radius of the circle, in the example below it is set to 0.4.
```
#22=IFCCARTESIANPOINT((0.,0.));
#23=IFCDIRECTION((1., 0.));
#24=IFCAXIS2PLACEMENT2D(#22, #23);
#25=IFCCIRCLEPROFILEDEF(.AREA., 'Circle', #24, 0.4);
```


## Footer
Just simple
```
ENDSEC;
END-ISO-10303-21;
```
