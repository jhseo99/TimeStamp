<?php
	$people = $_GET["people"];
	$id = $_COOKIE["id"];

	if(!isset($id))
	{
		setcookie("id", base64_encode("customer"), time()+60*10);
	}

	$id = base64_decode($id);

	if (isset($people))
	{
		switch ($people) 
		{
			case "customer":
				if ($id == "customer")
				{
					echo "<script>alert('You are bought gingerbread! -1,000,000,000$');</script>";
				}
				else
				{
					echo "<script>alert('You are not customer. Only customer can buy my gingerbread!');</script>";
				}
				break;
			case "baker":
				if ($id == "baker")
				{
					echo "<script>alert('flag{giNg3R_is_N0t_de1iciouS_But_giNg3r_Bread_is_Yummy_yuMMy}');</script>";
				}
				else
				{
					echo "<script>alert('You are not baker. Only baker can bake gingerbread!');</script>";
				}
				break;
			default:
				break;
		}
	}
?>

<div class="wrapper col2">
	<table>
		<thead>
			<tr>
				<th>1</th>
				<th>2</th>
				<th>3</th>
			</tr>
		</thead>
		<tbody style="background-color: #F7AA39; font-size: 22px; padding: 5px">
			<tr>
				<td><a href="index.php?page=bread&people=customer">BUY</a></td>
				<td><a href="index.php?page=bread&people=baker">BAKE</a></td>
				<td><a href="index.php">EXIT</a></td>
			</tr>
		</tbody>
	</table>
</div>