$fn= $preview ? 32 : 256;
d_max = 42;
h_max = 65;
esp_x = 56;
esp_y = 28;
esp_z = 14;
esp_inner_pin_y = 20;
esp_inner_pin_z = 6;
wall_thickness = 2;
space = 1;

outerCylinder();
translate([(esp_y + 2* space)/-2, d_max/2 - 2*wall_thickness - 5, wall_thickness]) espClip();

module espClip() {
    cube([esp_y + 2* space, wall_thickness, esp_x]);
    translate([(esp_y - esp_inner_pin_y)/2 + space, (esp_inner_pin_z + 2* wall_thickness) * -1, 0]) cube([esp_inner_pin_y, wall_thickness*2, esp_x - wall_thickness]);
    translate([esp_y/2 + space -wall_thickness, (esp_inner_pin_z + 4* wall_thickness) * -1, 0]) cube([wall_thickness*2, wall_thickness*2, esp_x - 2*wall_thickness]);
}

module outerCylinder() {
    difference() {
        cylinder(h=h_max, d=d_max);
        translate([0, 0, wall_thickness]) cylinder(h=h_max - wall_thickness , d=d_max - 2* wall_thickness );
    }

}