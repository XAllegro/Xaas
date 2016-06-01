#include <XaLibGeo.h>

#include <XaLibBase.h>
#include <XaLibLog.h>
#include <XaLibChar.h>
#include <math.h>

XaLibGeo::XaLibGeo(){
};

vector<string> XaLibGeo::GetCartesian(string& Latitude,string& Longitude) {
	
//	float deg_to_rad=0.0174533;
	double earth_range=6370;
	double pi_180=0.01745329251;
		
	//From String to Float
	
	
	double latitude=atof(Latitude.c_str())* pi_180	;
	double longitude=atof(Longitude.c_str())* pi_180;
	
	double cos_lat=cos(latitude);

	double x=earth_range*cos_lat*cos(longitude);
	double y=earth_range*cos_lat*sin(longitude);
	double z=earth_range*sin(latitude);

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Calculated Cartesian Coordinates -> " +to_string(x)+" - "+to_string(y)+" - "+to_string(z));
	
	vector<string> xyz ={to_string(x),to_string(y),to_string(z)};	

	return xyz;
};

XaLibGeo::~XaLibGeo(){
};
