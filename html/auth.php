<?php

$authorized = FALSE;
$authfile = file("authfile.txt");

if (!isset($_SERVER['PHP_AUTH_USER']) || !isset($_SERVER['PHP_AUTH_PW'])) {
	header("WWW-Authenticate");
	header("HTTP/1.1 401 Unauthorized");
} else if (in_array($_SERVER['PHP_AUTH_USER'].":".$_SERVER['PHP_AUTH_PW']."\n", $authfile)) {
	$authorized = TRUE;
	echo "<p>welcome,".$_SERVER['PHP_AUTH_USER']."</p>";
} else {
	header("HTTP/1.0 401 Unauthorized");
	echo("<p>wrong password!</p>");
	exit;
}

if (! $authorized)
	exit;

// restricted content here

?>
