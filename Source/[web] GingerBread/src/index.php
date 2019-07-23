<?php
	$page = $_GET['page'];
	if (!isset($page) || $page == "") 
	{
		$page = "main";
	}
	if ($page != "main" && $page != "people" && $page != "bread")
	{
		$page = "main";
	}
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN"   
"http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
	<title>Yummy! Yummy! GingerBread</title>
	<link rel="stylesheet" type="text/css" href="css/style.css"/>
	<link rel="stylesheet" type="text/css" href="css/layout.css"/>
	<meta name="viewport" content="width=device-width, initial-scale=1.0"/>
</head>
<body id="top">
<div class="wrapper col1">
	<div id="header">
		<div id="topnav">
			<ul>
				<li><a href="index.php?page=bread">Bread</a></li>
				<li><a href="index.php?page=people">People</a></li>
				<li><a href="index.php">Home</a></li>
			</ul>						
		</div>
		<div class="fl_left">
			<h1><a href="index.php">YummyYummy Bakery</a></h1>
			<p>Ginger Bread</p>
		</div>
	</div>
</div>
<?php include($page.".php"); ?>
</body>
</html>