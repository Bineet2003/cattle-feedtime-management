<?php
    $filename = "cattle_data.txt";

    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        $cattleIdToRemove = $_POST["removeCattleId"];

        $lines = file($filename, FILE_IGNORE_NEW_LINES);
        $updatedLines = array_filter($lines, function($line) use ($cattleIdToRemove) {
            return !strpos($line, $cattleIdToRemove);
        });

        $data = implode(PHP_EOL, $updatedLines);
        file_put_contents($filename, $data);

        echo "Cattle data removed successfully.";
    }
?>
