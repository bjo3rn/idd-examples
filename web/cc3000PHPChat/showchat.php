<html>
<head>
	<meta http-equiv="refresh" content="3">
</head>
<body>
<h3>cc3000 chat</h3>
<pre>
<?php
 $chat = file_get_contents('./chat.txt');
 echo htmlspecialchars($chat);
?>	
</pre>
</body>

</html>