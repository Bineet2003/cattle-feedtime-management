<?php
    $filename = "cattle_data.txt";

    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        $cattleId = $_POST["cattleId"];
        $cattleName = $_POST["cattleName"];
        $feedTime = $_POST["feedTime"];
        $food = $_POST["food"];

        $data = $cattleId . " " . $cattleName . " " . $feedTime . " " . $food . PHP_EOL;
        file_put_contents($filename, $data, FILE_APPEND);

        echo "Cattle data added successfully.";
    }
?>
