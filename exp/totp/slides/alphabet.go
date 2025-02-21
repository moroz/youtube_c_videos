package main

import (
	"fmt"
	"strconv"
)

const BASE32_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"

func main() {
	fmt.Println(`<table class="alphabet"><tbody>`)
	for y := range 6 {
		fmt.Println(`<tr>`)
		for x := range 6 {
			value := x*6 + y
			if value >= 32 {
				continue
			}
			binary := strconv.FormatInt(int64(value), 2)

			for len(binary) < 5 {
				binary = "0" + binary
			}

			fmt.Printf(`<td><div><span class="letter">%s</span> <span class="binary">0b%s</span> <span class="int">%d</span></div></td>`, string(BASE32_ALPHABET[value]), binary, value)
		}
		fmt.Println(`</tr>`)
	}
	fmt.Println(`</tbody></table>`)
}
