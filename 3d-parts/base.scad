ps_x = 163;
ps_y = 42;
ps_z = 32;

toggle_x = 13;
toggle_y = 19.5;
toggle_z = 22;

x_max = 220;

wall_thickness = 2;
space = 3;

module psBox() {
    difference() {
        cube([ps_y+2*space+2*wall_thickness, x_max,]ps_z + space + wall_thickness);
        translate([wall_thickness, wall_thickness, wall_thickness]) cube([])
    }
}