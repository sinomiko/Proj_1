/**
 * Created by Miko on 2017/11/23.
 */
class Animal{
    private  String name;
    private  int weight;
    private  String sound;
    public void setName(String name_)
    {
        name = name_;
    }
    public String getName(){
        return name;
    }
    public  void setWeight(int weight_)
    {
        if (weight_>0)
        {
            weight = weight_;
        }

        else {
            System.out.println("weight must be bigger than 0");
        }
    }

    public  int getWeight(){
        return weight;
    }

    public  void setSound(String sound_)
    {
        sound = sound_;
    }


    public  String getSound (){
        return  sound;
    }
}

class  Dog extends  Animal{
    public void digHole(){
        System.out.println("dug a hole");
    }
    public Dog(){
        super();
        setSound("bark");
    }
    public void setVar(String Var)
    {
        Var = "world";
    }
}

class  Cat extends  Animal{
    public void digHole(){
        System.out.println("climbing a tree");
    }
    public Cat(){
        super();
        setSound("meow");
    }

}

public class test {
    public static void main( String[] args ) {
        Dog fido = new Dog();
        fido.setName("Fido");
        fido.setWeight(-1);
        System.out.println(fido.getName());
        fido.digHole();

        String x = new String("hello");
        fido.setVar(x);
        System.out.println(x);


        Animal doggy = new Dog();
        Animal kitty = new Cat();
        System.out.println("doggy says: " + doggy.getSound());
        System.out.println("kitty says: " + kitty.getSound());
        ((Dog)doggy).digHole();

        Animal[] animals = new Animal[4];
        animals[0] = doggy;
        animals[1] = kitty;
        System.out.println("doggy says: " + animals[0].getSound());
        System.out.println("kitty says: " + animals[1].getSound());

        speakAnimal(animals[0]);
    }
    public  static  void speakAnimal(Animal randAnimal){
        System.out.println("Animal says: "+ randAnimal.getSound());
    }
}
