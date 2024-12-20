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


## Let's create a cylinder

#### Base
At first, we need to define base of the cylinder, which is simple circle. The circle will be created in 2D space, so we need to define it's position position with **IFCCARTESIANPOINT** and direction of X-axis with **IFCDIRECTION**. This coordinates doesn't matter for the future cylinder placement. The circle is then simply created with **IFCCIRCLEPROFILEDEF**. The fourth parameter is the radius of the circle, in the example below it is set to 0.4.
```
#22=IFCCARTESIANPOINT((0.,0.));
#23=IFCDIRECTION((1., 0.));
#24=IFCAXIS2PLACEMENT2D(#22, #23);
#25=IFCCIRCLEPROFILEDEF(.AREA., 'Circle', #24, 0.4);
```

#### From circle to cylinder
The following code snippet will place the circle to the **(0, 0, 0)** position with **IFCAXIS2PLACEMENT3D**, extrude it upwards by **60.240** with **IFCEXTRUDEDAREASOLID** (the upward direction is simply the direction of Z-axis, which is **(0, 0, 1)**). Then we need  to set **IFCSHAPEREPRESENTATION** and **IFCPRODUCTDEFINITIONSHAPE**.
```
#26=IFCCARTESIANPOINT((0., 0., 0.));
#27=IFCAXIS2PLACEMENT3D(#26, $, $);
#28=IFCDIRECTION((0., 0., 1.));
#29=IFCEXTRUDEDAREASOLID(#25, #27, #28, 60.240);
#30=IFCSHAPEREPRESENTATION(#11, 'Body', 'SweptSolid', (#29));
#31=IFCPRODUCTDEFINITIONSHAPE($, $, (#30));
```

#### Placement of the cylinder
Finally, we need to place our cylinder to the 3D space in our project. With **IFCCARTESIANPOINT** we set the position of the base, then we need to set direction both for Z-axis and X-axis. Since we extruded our cylinder upwards (thus along the Z-axis), the direction of the Z-axis will be the desired direction of the cylinder, in this case **(10.831, -59.252, -0.868)** (The size of this vector doesn't matter, just the direction). We don't need to set direction of the X-axis, so it will remain default **(1, 0, 0)**. We will combine these values in **IFCAXIS2PLACEMENT3D** and then place it to the space with **IFCLOCALPLACEMENT**. As the last step we will make **IFCBUILDINGELEMENTPROXY** for the cylinder and the link it to the site with **IFCRELCONTAINEDINSPATIALSTRUCTURE**.
```
#32=IFCCARTESIANPOINT((1195.173, 145.661, 302.877));
#33=IFCDIRECTION((10.831, -59.252, -0.868));
#34=IFCDIRECTION((1., 0., 0.));
#35=IFCAXIS2PLACEMENT3D(#32, #33, #34);
#36=IFCLOCALPLACEMENT($, #35);
#37=IFCBUILDINGELEMENTPROXY('0qs7mimyyHvuvRW1aqWGIT', #5, 'Potrubi', $, $, #36, #31, $, $);
#38=IFCRELCONTAINEDINSPATIALSTRUCTURE('26c$dAXGL3AOHiH_WcC123', #6, 'Site to geometries link', $, (#37), #21);
```


## Footer
Just simple
```
ENDSEC;
END-ISO-10303-21;
```
