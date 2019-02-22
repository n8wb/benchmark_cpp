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

    a_vec := make([]int,len1)
    for i := 0; i < len1; i++ {
        a_vec[i] = rng.Intn(1000000000)
    }
    
    fmt.Printf("%d\n",len1)
    for i,val := range a_vec {
        if i == 0{
            fmt.Printf("%d",val)
        }else{
            fmt.Printf(" %d",val)
        }
        
    }
    fmt.Println("")    
}
