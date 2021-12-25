<?php

$in = "data.txt";
if (!file_exists($in)) {
    echo "$in file not exist";
    return;
}
$fo = fopen($in, "r");

$width = 0;
$i = 0;
$j = 0;
$height = 0;
$sea = array();

while ($char = fgetc($fo)) {
    if ($char === PHP_EOL) {
        $i = 0;
        $j++;
    } else {
        $sea[$j][$i] = $char;
        $i++;
    }
}
function printsea(array $sea)
{
    echo "=====================" . PHP_EOL;
    foreach ($sea as $sealine) {
        foreach ($sealine as $char) {
            print $char;
        }
        print PHP_EOL;
    }
}

function step(array $sea, $w, $h)
{
    $newsea = $sea;
    $moved = 0;
    foreach ($sea as $i => $sealine) {
        foreach ($sealine as $j => $char) {
            if ($char === '>') {
                if ($j === $w) {
                    $newj = 0;
                } else {
                    $newj = $j + 1;
                }
                if ($sea[$i][$newj] === '.') {
                    $moved++;
                    $newsea[$i][$newj] = '>';
                    $newsea[$i][$j] = '.';
                }
            }
        }
    }
    $sea = $newsea;
    foreach ($sea as $i => $sealine) {
        foreach ($sealine as $j => $char) {
            if ($char === 'v') {
                if ($i === $h) {
                    $newi = 0;
                } else {
                    $newi = $i + 1;
                }
                if ($sea[$newi][$j] === '.') {
                    $moved++;
                    $newsea [$newi][$j] = 'v';
                    $newsea[$i][$j] = '.';
                }
            }
        }
    }
    return [$moved, $newsea];
}

$height = count($sea) - 1;
$width = count($sea[0]) - 1;
printsea($sea);
$turns = 0;
do {
    [$moves, $sea] = step($sea, $width, $height);
    printsea($sea);
    $turns++;
} while ($moves > 0);

echo "turns $turns";