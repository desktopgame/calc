package main

import (
	"fmt"
	"os/exec"
)

func execp(name string, args ...string) {
	//実行するコマンドを表示する
	fmt.Printf(name)
	fmt.Printf(" : ")
	for _, e := range args {
		fmt.Printf(" %s", e)
	}
	fmt.Println()
	//実行する
	out, err := exec.Command(name, args...).Output()
	if err != nil {
		fmt.Println("    error")
	}
	fmt.Println(string(out))
	fmt.Println()
}

func main() {
	execp("flex", "calc.l")
	execp("bison", "-d", "calc.y", "-r", "all")
}
