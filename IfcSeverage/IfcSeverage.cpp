// IfcSeverage.cpp : Defines the entry point for the application.
//

#include "IfcSeverage.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip> // For std::setprecision
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <array>



std::string doubleToStringWithThreeDecimals(double value)
{
	std::ostringstream out; out << std::fixed << std::setprecision(3) << value; return out.str();
}


//VZOR:
// #21=IFCCARTESIANPOINT((0.,0.));
// #22 = IFCDIRECTION((1., 0.));
// #23 = IFCAXIS2PLACEMENT2D(#21, #22);
// #24 = IFCCIRCLEPROFILEDEF(.AREA., 'Circle', #23, 0.4);
// #25 = IFCCARTESIANPOINT((0., 0., 0.));
// #26 = IFCAXIS2PLACEMENT3D(#25, $, $);
// #27 = IFCDIRECTION((0., 0., 1.));
// #28 = IFCEXTRUDEDAREASOLID(#24, #26, #27, 2.);
// #29 = IFCSHAPEREPRESENTATION(#11, 'Body', 'SweptSolid', (#28));
// #30 = IFCPRODUCTDEFINITIONSHAPE($, $, (#29));
// #31 = IFCCARTESIANPOINT((0., 0., 0.));
// #32 = IFCDIRECTION((1.0, 0.0, 5.0));
// #33 = IFCDIRECTION((1., 0., 0.));
// #34 = IFCAXIS2PLACEMENT3D(#31, #32, #33);
// #35 = IFCLOCALPLACEMENT($, #34);
// #36 = IFCBUILDINGELEMENTPROXY('0qs7mimyyHvuvRW1aqWGIT', #5, 'Potrubi', $, $, #35, #30, $, $);
// samotný výpis ifc válce
void writeCylinder(std::ostream& outStream, int& lineCounter, double x_poc, double y_poc,  double z_poc, double delka, double dx, double dy, double dz)
{


	outStream << "#" << lineCounter + 1 << "=IFCCARTESIANPOINT((0.,0.));" << std::endl;
	outStream << "#" << lineCounter + 2 << "=IFCDIRECTION((1., 0.));" << std::endl;
	outStream << "#" << lineCounter + 3 << "=IFCAXIS2PLACEMENT2D(#" << lineCounter + 1 << ", #" << lineCounter + 2 << ");" << std::endl;
	outStream << "#" << lineCounter + 4 << "=IFCCIRCLEPROFILEDEF(.AREA., 'Circle', #" << lineCounter + 3 << ", 0.4);" << std::endl;
	outStream << "#" << lineCounter + 5 << "=IFCCARTESIANPOINT((0., 0., 0.));" << std::endl;
	outStream << "#" << lineCounter + 6 << "=IFCAXIS2PLACEMENT3D(#" << lineCounter + 5 << ", $, $);" << std::endl;
	outStream << "#" << lineCounter + 7 << "=IFCDIRECTION((0., 0., 1.));" << std::endl;
	outStream << "#" << lineCounter + 8 << "=IFCEXTRUDEDAREASOLID(#" << lineCounter + 4 << ", #" << lineCounter + 6 << ", #" << lineCounter + 7 << ", " << doubleToStringWithThreeDecimals(delka) << ");" << std::endl;
	outStream << "#" << lineCounter + 9 << "=IFCSHAPEREPRESENTATION(#11, 'Body', 'SweptSolid', (#" << lineCounter + 8 << "));" << std::endl;
	outStream << "#" << lineCounter + 10 << "=IFCPRODUCTDEFINITIONSHAPE($, $, (#" << lineCounter + 9 << "));" << std::endl;
	outStream << "#" << lineCounter + 11 << "=IFCCARTESIANPOINT((" << doubleToStringWithThreeDecimals(x_poc) << ", " << doubleToStringWithThreeDecimals(y_poc) << ", " << doubleToStringWithThreeDecimals(z_poc) << "));" << std::endl;
	outStream << "#" << lineCounter + 12 << "=IFCDIRECTION((" << doubleToStringWithThreeDecimals(dx) << ", " << doubleToStringWithThreeDecimals(dy) << ", " << doubleToStringWithThreeDecimals(dz) << "));" << std::endl;
	outStream << "#" << lineCounter + 13 << "=IFCDIRECTION((1., 0., 0.));" << std::endl;
	outStream << "#" << lineCounter + 14 << "=IFCAXIS2PLACEMENT3D(#" << lineCounter + 11 << ", #" << lineCounter + 12 << ", #" << lineCounter + 13 << ");" << std::endl;
	outStream << "#" << lineCounter + 15 << "=IFCLOCALPLACEMENT($, #" << lineCounter + 14 << ");" << std::endl;
	outStream << "#" << lineCounter + 16 << "=IFCBUILDINGELEMENTPROXY('0qs7mimyyHvuvRW1aqWGIT', #5, 'Potrubi', $, $, #" << lineCounter + 15 << ", #" << lineCounter + 10 << ", $, $);" << std::endl;
	outStream << "#" << lineCounter + 17 << "=IFCRELCONTAINEDINSPATIALSTRUCTURE('26c$dAXGL3AOHiH_WcC123', #6, 'Site to geometries link', $, (#" << lineCounter + 16 << "), #21);" << std::endl;

	lineCounter += 17;

	outStream << std::endl;
	outStream << std::endl;
	outStream << std::endl;
}

void writeHeader(std::ostream& outStream, int& lineCounter)
{
	outStream << "ISO-10303-21;" << std::endl;
	outStream << "HEADER;" << std::endl;
	outStream << "FILE_DESCRIPTION(('ViewDefinition [CoordinationView]'), '2;1');" << std::endl;
	outStream << "FILE_NAME('cylinder.ifc', '2017-11-07T15:20:37', (''), (''), 'IfcOpenShell-0.5.0-dev', 'IfcOpenShell-0.5.0-dev', '');" << std::endl;
	outStream << "FILE_SCHEMA(('IFC2X3'));" << std::endl;
	outStream << "ENDSEC;" << std::endl;
	outStream << "DATA;" << std::endl;
	outStream << "#1=IFCPERSON($, $, '', $, $, $, $, $);" << std::endl;
	outStream << "#2=IFCORGANIZATION($, '', $, $, $);" << std::endl;
	outStream << "#3=IFCPERSONANDORGANIZATION(#1, #2, $);" << std::endl;
	outStream << "#4=IFCAPPLICATION(#2, '0.5.0-dev', 'IfcOpenShell-0.5.0-dev', '');" << std::endl;
	outStream << "#5=IFCOWNERHISTORY(#3, #4, $, .ADDED., $, #3, #4, 1510068037.0321496);" << std::endl;
	outStream << "#6=IFCDIRECTION((1., 0., 0.));" << std::endl;
	outStream << "#7=IFCDIRECTION((0., 0., 1.));" << std::endl;
	outStream << "#8=IFCCARTESIANPOINT((0., 0., 0.));" << std::endl;
	outStream << "#9=IFCAXIS2PLACEMENT3D(#8, #7, #6);" << std::endl;
	outStream << "#10=IFCDIRECTION((0., 1., 0.));" << std::endl;
	outStream << "#11=IFCGEOMETRICREPRESENTATIONCONTEXT($, 'Model', 3, 1.E-05, #9, #10);" << std::endl;
	outStream << "#12=IFCDIMENSIONALEXPONENTS(0, 0, 0, 0, 0, 0, 0);" << std::endl;
	outStream << "#13=IFCSIUNIT(*, .LENGTHUNIT., $, .METRE.);" << std::endl;
	outStream << "#14=IFCSIUNIT(*, .AREAUNIT., $, .SQUARE_METRE.);" << std::endl;
	outStream << "#15=IFCSIUNIT(*, .VOLUMEUNIT., $, .CUBIC_METRE.);" << std::endl;
	outStream << "#16=IFCSIUNIT(*, .PLANEANGLEUNIT., $, .RADIAN.);" << std::endl;
	outStream << "#17=IFCMEASUREWITHUNIT(IFCPLANEANGLEMEASURE(0.017453292519943295), #16);" << std::endl;
	outStream << "#18=IFCCONVERSIONBASEDUNIT(#12, .PLANEANGLEUNIT., 'DEGREE', #17);" << std::endl;
	outStream << "#19=IFCUNITASSIGNMENT((#13, #14, #15, #18));" << std::endl;
	outStream << "#20=IFCPROJECT('1ZjweOZ9L8xur3Cw4DWAdx', #5, '', $, $, $, $, (#11), #19);" << std::endl;
	outStream << "#21=IFCSITE('1_CIr7zc1D6OXv62_qHF7A', #6, $, $, $, $, $, $, .COMPLEX., $, $, $, $, $);" << std::endl;

	outStream << std::endl;
	outStream << std::endl;
	outStream << std::endl;

}

void writeFooter(std::ostream& outStream, int& lineCounter)
{
	outStream << "#" << lineCounter + 1 << "=IFCRELAGGREGATES('32lxp2EoH3aAt0ZI54g63R',#5,'Project to site link',$,#20,(#21));" << std::endl;
	outStream << "ENDSEC;" << std::endl;
	outStream << "END-ISO-10303-21; " << std::endl;
	lineCounter += 3;

	outStream << std::endl;
	outStream << std::endl;
	outStream << std::endl;
}

std::string smerString(std::string poc_str, std::string konc_str)
{
	std::replace(poc_str.begin(), poc_str.end(), ',', '.');
	std::replace(konc_str.begin(), konc_str.end(), ',', '.');
	try
	{
		double a = std::stod(poc_str);
		double b = std::stod(konc_str);
		return std::to_string(b - a);
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << "Invalid argument: " << e.what() << std::endl;
		return "0.0";
	}
	catch (const std::out_of_range& e)
	{
		std::cerr << "Out of range: " << e.what() << std::endl;
		return "0.0";
	}
}


std::vector<std::string> split(const std::string& line, char delimiter)
{
	std::vector<std::string> fields;
	std::stringstream ss(line);
	std::string field;
	while (getline(ss, field, delimiter))
	{
		fields.push_back(field);
	}
	return fields;
}


int main()
{
	std::ifstream file("fulnek.XLS");
	if (!file.is_open())
	{
		std::cerr << "Unable to open file" << std::endl;
		return 1;
	}

	std::string line;
	std::map<std::string, int> headerIndexMap;
	if (getline(file, line))
	{ // Read the header line
		std::vector<std::string> headers = split(line, '\t');
		for (int i = 0; i < headers.size(); ++i)
		{
			headerIndexMap[headers[i]] = i;
		}
	}


	std::vector<std::map<std::string, double>> data;

	int rowCounter = 21;

	while (getline(file, line))
	{
		std::vector<std::string> row = split(line, '\t');
		if (row.size() > 50)
		{

			std::map<std::string, double> rowMap;



			std::string x_poc = row[headerIndexMap["x poč. uzlu"]];
			std::replace(x_poc.begin(), x_poc.end(), ',', '.');
			std::string y_poc = row[headerIndexMap["y poč. uzlu"]];
			std::replace(y_poc.begin(), y_poc.end(), ',', '.');
			std::string z_poc = row[headerIndexMap["Poč. zaústění"]];
			std::replace(z_poc.begin(), z_poc.end(), ',', '.');
			std::string delka = row[headerIndexMap["Délka 3D"]];
			std::replace(delka.begin(), delka.end(), ',', '.');
			std::string dx = smerString(row[headerIndexMap["x poč. uzlu"]], row[headerIndexMap["x konc. uzlu"]]);
			std::string dy = smerString(row[headerIndexMap["y poč. uzlu"]], row[headerIndexMap["y konc. uzlu"]]);
			std::string dz = smerString(row[headerIndexMap["Poč. zaústění"]], row[headerIndexMap["Konc. zaústění"]]);


			rowMap["x poè. uzlu"] = std::stod(x_poc);
			rowMap["y poè. uzlu"] = std::stod(y_poc);
			rowMap["z poè. uzlu"] = std::stod(z_poc);
			rowMap["Délka 2D"] = std::stod(delka);
			rowMap["dx"] = std::stod(dx);
			rowMap["dy"] = std::stod(dy);
			rowMap["dz"] = std::stod(dz);
			data.push_back(rowMap);
		}
	}



	file.close();

	double minX = std::numeric_limits<double>::max();
	double minY = std::numeric_limits<double>::max();
	double minZ = std::numeric_limits<double>::max();

	for (auto& myMap : data)
	{
		if (myMap["x poè. uzlu"] < minX)
		{
			minX = myMap["x poè. uzlu"];
		}
		if (myMap["y poè. uzlu"] < minY)
		{
			minY = myMap["y poè. uzlu"];
		}
		if (myMap["z poè. uzlu"] < minZ)
		{
			minZ = myMap["z poè. uzlu"];
		}
	}

	for (auto& myMap : data)
	{
		myMap["x poè. uzlu"] -= minX;
		myMap["y poè. uzlu"] -= minY;
		myMap["z poè. uzlu"] -= minZ;
	}



	std::ofstream outputFile("output.ifc");

	// Check if the file is open
	if (outputFile.is_open())
	{
		writeHeader(outputFile, rowCounter);
		for (auto& map : data) // výpis do stdout
		{
			writeCylinder(outputFile, rowCounter, map["x poè. uzlu"], map["y poè. uzlu"], map["z poè. uzlu"], map["Délka 2D"], map["dx"], map["dy"], map["dz"]);
		}
		writeFooter(outputFile, rowCounter);

		// Close the file after writing
		outputFile.close();
		std::cout << "Data has been written to output.ifc" << std::endl;
	}
	else
	{
		// If the file could not be opened
		std::cerr << "Unable to open the file for writing." << std::endl;
	}


	return 0;
}
