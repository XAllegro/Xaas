// This example displays an address form, using the autocomplete feature
// of the Google Places API to help users fill in the information.

var placeSearch, autocomplete;
var componentForm = {
  street_number: 'short_name',
  route: 'long_name',
  locality: 'long_name',
  administrative_area_level_1: 'short_name',
  administrative_area_level_2: 'short_name',
  country: 'long_name',
  postal_code: 'short_name'
};

function initialize() {

	// Create the autocomplete object, restricting the search
	// to geographical location types.
	autocomplete = new google.maps.places.Autocomplete(
	/** @type {HTMLInputElement} */(document.getElementById('autocomplete')),
	{ types: ['geocode'] });

	// When the user selects an address from the dropdown,
	// populate the address fields in the form.

	google.maps.event.addListener(autocomplete, 'place_changed', function() {
		fillInAddress();
	});
}
// The START and END in square brackets define a snippet for our documentation:
// [START region_fillform]
function fillInAddress() {

	// Get the place details from the autocomplete object.
	var place = autocomplete.getPlace();
	
	document.getElementById('longitude').value =place.geometry.location.lng();
	document.getElementById('latitude').value =place.geometry.location.lat();
	//alert(place.geometry.location.lat());
	//alert(place.geometry.location.lng());
	
	for (var component in componentForm) {
		document.getElementById(component).value = '';
		document.getElementById(component).disabled = false;
	}

	// Get each component of the address from the place details
	// and fill the corresponding field on the form.
	for (var i = 0; i < place.address_components.length; i++) {
		var addressType = place.address_components[i].types[0];

		if (componentForm[addressType]) {
			var val = place.address_components[i][componentForm[addressType]];
			document.getElementById(addressType).value = val;
		}
	}
}

// [END region_fillform]
// [START region_geolocation]
// Bias the autocomplete object to the user's geographical location,
// as supplied by the browser's 'navigator.geolocation' object.
function geolocate() {

//MODIFICATO PER NON RICHIEDERE LA TUA POSIZIONE
  //if (navigator.geolocation) {
    //navigator.geolocation.getCurrentPosition(function(position) {
	//var geolocation = new google.maps.LatLng( position.coords.latitude, position.coords.longitude );	  
	//autocomplete.setBounds(new google.maps.LatLngBounds(geolocation,geolocation));

  //  });

//}
}

// [END region_geolocation]
function loadScript() {
  var script = document.createElement('script');
  script.type = 'text/javascript';
  script.src = 'https://maps.googleapis.com/maps/api/js?v=3.exp&sensor=false&libraries=places&' +'callback=initialize';
  document.body.appendChild(script);
}