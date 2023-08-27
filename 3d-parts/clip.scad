space = 1;
stripZ = 9;
stripY = 12;
stripX = 150;
stripYCutOut = 10;
stripHolderThickness = 2;

rotate(a=[25,0,0]) ledHolder();

module ledHolder() {
    difference() {
        cube([stripX, stripY + 2*space + 2*stripHolderThickness, stripZ + 2*space + 2*stripHolderThickness]);
        translate([0, stripHolderThickness, stripHolderThickness]) cube([stripX, stripY + 2*space, stripZ + space]);
        translate([0, (stripY - stripYCutOut)/2 + space + stripHolderThickness, stripZ + space + stripHolderThickness]) cube([stripX, stripYCutOut, space + stripHolderThickness]);
    }
}