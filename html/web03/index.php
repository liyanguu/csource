<!DOCTYPE html>
<html>

<head>
<title>page with many pictures</title>
</head>

<body>
<?php
	$pics = file("img/picindex.txt");

	foreach ($pics as $pic) 
		echo "<p><a href=\"img/$pic\"></a><br />$pic</p>";
?>
</body>

</html>
