<?php
    $filename = "cattle_data.txt";

    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        if (isset($_POST["displayByTime"])) {
            displayDataByTime($filename);
        } elseif (isset($_POST["displayById"])) {
            displayDataById($filename);
        }
    }

    function displayDataByTime($filename) {
        $lines = file($filename, FILE_IGNORE_NEW_LINES);

        $currentTime = time();
        $currentTimeInfo = localtime($currentTime, true);

        usort($lines, function($a, $b) use ($currentTimeInfo) {
            $feedTimeA = explode(" ", $a)[2];
            $feedTimeB = explode(" ", $b)[2];

            $timeA = strtotime($feedTimeA);
            $timeB = strtotime($feedTimeB);

            $diffMinutesA = (($timeA / 60) % 1440) - (($currentTimeInfo["tm_hour"] * 60) + $currentTimeInfo["tm_min"]);
            $diffMinutesB = (($timeB / 60) % 1440) - (($currentTimeInfo["tm_hour"] * 60) + $currentTimeInfo["tm_min"]);

            if ($diffMinutesA < 0)
                $diffMinutesA += 24 * 60;
            if ($diffMinutesB < 0)
                $diffMinutesB += 24 * 60;

            $diffSecondsA = $diffMinutesA * 60;
            $diffSecondsB = $diffMinutesB * 60;

            return $diffSecondsA - $diffSecondsB;
        });

        echo "Cattle ID | Cattle Name | Feed Time | Food | Time Difference" . "<br>";
        foreach ($lines as $line) {
            $data = explode(" ", $line);
            $feedTime = $data[2];

            $time = strtotime($feedTime);
            $diffMinutes = (($time / 60) % 1440) - (($currentTimeInfo["tm_hour"] * 60) + $currentTimeInfo["tm_min"]);

            if ($diffMinutes < 0)
                $diffMinutes += 24 * 60;

            $diffSeconds = $diffMinutes * 60;
            $diffHours2 = floor($diffSeconds / 3600);
            $diffMinutes2 = floor(($diffSeconds - ($diffHours2 * 3600)) / 60);

            echo $data[0] . " | " . $data[1] . " | " . $feedTime . " | " . $data[3] . " | " . $diffHours2 . " hours " . $diffMinutes2 . " minutes" . "<br>";
        }
    }

    function displayDataById($filename) {
        $lines = file($filename, FILE_IGNORE_NEW_LINES);
        sort($lines);

        echo "Cattle ID | Cattle Name | Feed Time | Food" . "<br>";
        foreach ($lines as $line) {
            $data = explode(" ", $line);
            echo $data[0] . " | " . $data[1] . " | " . $data[2] . " | " . $data[3] . "<br>";
        }
    }
?>
