<?php
if (isset($_POST['save'])) {
    $msg = "";
    $name = $_POST['name'];
    $age = $_POST['age'];
    $gender = $_POST['gender'];


    $xml = "<?xml version='1.0' encoding='UTF-8'?>
    <student>
        <name>" . htmlspecialchars($name) . "</name>
        <age>" . htmlspecialchars($age) . "</age>
        <gender>" . htmlspecialchars($gender) . "</gender>
    </student>";

    $dom = new DOMDocument();
    libxml_use_internal_errors(true);
    $dom->preserveWhiteSpace = false;

    // 2. Validate
    if ($dom->loadXML($xml) && $dom->schemaValidate('validate.xsd')) {
        $msg = "<p style='color:green'><b>Success!</b> SuccessFully Validated</p><br>
            with the xml content:<br><pre>" . htmlspecialchars($xml) . "</pre>";

    } else {
        $msg = "<div style='color:red'><b>Validation Errors:</b><ul>";
        foreach (libxml_get_errors() as $e) {
            $raw = $e->message;
            echo "$raw<br>";
            if (strpos($raw, "name") !== false) {
                $msg .= "Please use a valid name (only letters and spaces allowed).<br>";
            }
            if (strpos($raw, "age") !== false) {
                $msg .= "Please use a valid age (a num between 1 and 120).<br>";
            }

            if (strpos($raw, "gender") !== false) {
                $msg .= "Please select a valid gender (Male or Female).<br>";
            }
        }
        $msg .= "</ul></div>";
        libxml_clear_errors();
    }
}
?>

<!DOCTYPE html>
<html>

<body>
    <h2>Student XML Editor</h2>
    <?php echo $msg; ?>

    <form method="post">
        Name: <input type="text" name="name"><br><br>
        Age: <input type="text" name="age"><br><br>
        Gender:
        <select name="gender">
            <option value="Male">Male</option>
            <option value="Female">Female</option>
        </select><br><br>
        <button type="submit" name="save">Validate</button>
    </form>
</body>

</html>