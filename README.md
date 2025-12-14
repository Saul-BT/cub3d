# cub3d

how to clone (pulling all library dependencies submodules)
```bash
git clone --recurse-submodules git@github.com:Saul-BT/cub3d.git
```
or
```bash
git clone git@github.com:Saul-BT/cub3d.git
cd cub3d
git submodule update --init --recursive
```
## leak check
```
valgrind --suppressions=mlx42.supp --leak-check=full --show-leak-kinds=all ./cub3d assets/maps/simple.cub
```