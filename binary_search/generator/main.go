package main

import(
    "bufio"
    "fmt"
    "os"
    "strings"
    "strconv"
    "time"
    "math/rand"
)


func main(){
    reader := bufio.NewReader(os.Stdin)
    text, _ := reader.ReadString('\n')
    inputs := strings.Split(text," ")
    if len(inputs) < 3 {
        panic("Missing inputs")
    }
    len1,err := strconv.Atoi(inputs[0])
    if err != nil{
        panic(err)
    }
    len2,err := strconv.Atoi(inputs[1])
    if err != nil{
        panic(err)
    }
    odds,err := strconv.ParseFloat(inputs[2][:len(inputs[2])-1],64)
    if err != nil{
        panic(err)
    }
    s1 := rand.NewSource(time.Now().UnixNano())
    rng := rand.New(s1)

    a_vec := make([]int,len1)
    for i := 0; i < len1; i++ {
        a_vec[i] = rng.Intn(1000000000)
    }
    b_vec := make([]int,len2)

    for i,_ := range b_vec {
        chance := rng.Float64()
        if chance <= odds {
            b_vec[i] = a_vec[rng.Intn(len1)]
        }else{
            b_vec[i] = rng.Intn(1000000000)
        }
    }
    fmt.Printf("%d",len1)
    for _,val := range a_vec {
        fmt.Printf(" %d",val)
    }
    fmt.Println("")
    fmt.Printf("%d",len2)
    for _,val := range b_vec {
        fmt.Printf(" %d",val)
    }
    fmt.Println("")
    
}
