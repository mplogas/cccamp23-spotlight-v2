space = 1;
stripZ = 9;
stripY = 12;
stripX = 50;
stripYCutOut = 10;
stripHolderThickness = 2;
stripAngle = 25;
holderZ = 2;
holderBaseY = 4;
holderBaseZ = 2;

union(){
    hull() {
        holderBase();
        translate([0,holderBaseY/2, holderBaseZ + holderBaseZ]) rotate(a=[stripAngle,0,0]) cube([stripX, stripY + 2*space + 2*stripHolderThickness, 1]);
    }
    translate([0,holderBaseY/2, holderBaseZ + holderBaseZ]) rotate(a=[stripAngle,0,0]) ledHolder();
}


module holderBase() {
    union() {
        cube([stripX, stripY + 2*space + 2*stripHolderThickness + holderBaseY, holderBaseZ]);
        translate([0, holderBaseY / 2, holderBaseZ]) cube([stripX, stripY + 2*space + 2*stripHolderThickness, holderZ]);
    }
}

module ledHolder() {
    difference() {
        cube([stripX, stripY + 2*space + 2*stripHolderThickness, stripZ + 2*space + 2*stripHolderThickness]);
        translate([0, stripHolderThickness, stripHolderThickness]) cube([stripX, stripY + 2*space, stripZ + space]);
        translate([0, (stripY - stripYCutOut)/2 + space + stripHolderThickness, stripZ + space + stripHolderThickness]) cube([stripX, stripYCutOut, space + stripHolderThickness]);
    }
}