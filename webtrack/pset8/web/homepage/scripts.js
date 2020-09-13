function getlocation()
{
    navigator.geolocation.getCurrentPosition(function(position) {
        document.querySelector("#location").innerHTML = "Your location is: " + position.coords.latitude + ", " + position.coords.longitude
	});
}
