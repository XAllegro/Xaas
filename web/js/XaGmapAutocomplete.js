var placeSearch, autocomplete;

var componentForm = {
  "street_number-input": "short_name",
  "route-input": "long_name",
  "locality-input": "long_name",
  "administrative_area_level_1-input": "short_name",
  "administrative_area_level_2-input": "short_name",
  "country-input": "long_name",
  "postal_code-input": "short_name"
};

function initialize() {
 
	autocomplete = new google.maps.places.Autocomplete((document.getElementById('autocomplete-input')),{ types: ['geocode'] });

	google.maps.event.addListener(autocomplete, 'place_changed', function() {
		fillInAddress();
	});
}

function fillInAddress() {

	var place = autocomplete.getPlace();

	document.getElementById('longitude-input').value =place.geometry.location.lng();
	document.getElementById('latitude-input').value =place.geometry.location.lat();
	//alert(place.geometry.location.lat());
	//alert(place.geometry.location.lng());

	for (var component in componentForm) {

		document.getElementById(component).value = '';
		document.getElementById(component).disabled = false;
	}

    /*RETURNED OBJECTS WITH DATA*/
	//console.log(place.address_components);
    //console.log(place.address_components.length);

    for (var i = 0; i < place.address_components.length; i++) {
        
		var addressType = place.address_components[i].types[0]+"-input";
        
		if (componentForm[addressType]) {
			var val = place.address_components[i][componentForm[addressType]];
            
			document.getElementById(addressType).value = val;
		}
	}
}

function geolocate() {

//MODIFICATO PER NON RICHIEDERE LA TUA POSIZIONE
  //if (navigator.geolocation) {
    //navigator.geolocation.getCurrentPosition(function(position) {
	//var geolocation = new google.maps.LatLng( position.coords.latitude, position.coords.longitude );	  
	//autocomplete.setBounds(new google.maps.LatLngBounds(geolocation,geolocation));

  //  });
//}
}

function LoadGeoScript() {
  var script = document.createElement('script');
  script.type = 'text/javascript';
  script.src = 'https://maps.googleapis.com/maps/api/js?v=3.exp&sensor=false&libraries=places&' +'callback=initialize';
  document.body.appendChild(script);
}