package main

import(
    "bufio"
    "fmt"
    "os"
    "strconv"
    "time"
    "math/rand"
)


func main(){
    reader := bufio.NewReader(os.Stdin)
    text, _ := reader.ReadString('\n')
    len1,err := strconv.Atoi(text[:len(text)-1])
    if err != nil{
        panic(err)
    }
    s1 := rand.NewSource(time.Now().UnixNano())
    rng := rand.New(s1)

    out := make([]byte,len1)
    for i := 0; i < len1; i++ {
        out[i] = byte(97 + rng.Intn(25))
    }
    if err != nil {
        panic(err)
    }

    fmt.Println(string(out))

}