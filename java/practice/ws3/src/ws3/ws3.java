package ws3;

// base class 
class Shape  
{ 
	String color;
	Boolean filled;
	
	public Shape() {
		this.color = "green";
		this.filled = true;
	}
	
	public Shape(String color, Boolean filled) {
		this.color = color;
		this.filled = filled;
	}
	
	public String getColor()
	{
		return this.color;
	}
	
	public boolean isFilled()
	{
		return filled;
	}
	
	public void setColor(String color)
	{
		this.color = color;
	}
	
	public void setFilled(Boolean filled)
	{
		this.filled = filled;
	}
	
	public String toString() {
		return ("A sape with color of " + getColor() + " and filled: " + isFilled());
	}
	
	public double getArea() {return 0;}
	public double getPerimeter() {return 0;}
} 

class Circle extends Shape{
	double radius;
	static double pie = 3.14;
	
	public Circle() {
		super();
		radius = 1.0;
	}
	
	public Circle(double radius) {
		super();
		this.radius = radius;
	}
	
	public Circle(double radius, String color, Boolean filled) {
		super(color, filled);
		this.radius = radius; 
	}
	
	public double getRadius() {
		return radius;
	}
	
	public void setRadius(double radius) {
		this.radius = radius;
	}
	
	@Override
	public double getArea() {
		return Circle.pie * radius * radius;
	}
	
	@Override
	public double getPerimeter() {
		return 2 * Circle.pie * radius;
	}
	
	@Override
	public String toString() {
		return ("A Circle with radius " + getRadius() + ", which is subclass of " + super.toString());
	}
}

class Rectangle extends Shape{
	double width;
	double length;
	
	public Rectangle() {
		super();
		width = 1.0;
		length = 1.0;
	}
	
	public Rectangle(double width, double length) {
		super();
		this.width = width;
		this.length = length;
	}
	
	public Rectangle(double width, double length, String color, Boolean filled) {
		super(color, filled);
		this.width = width;
		this.length = length;
	}
	
	public double getWidth() {
		return width;
	}
	
	public void setWidth(double width) {
		this.width = width;
	}
	
	public double getLength() {
		return length;
	}
	
	public void setLength(double length) {
		this.length = length;
	}
	
	@Override
	public double getArea() {
		return length * width;
	}
	
	@Override
	public double getPerimeter() {
		return (length * 2) + (width * 2);
	}
	
	@Override
	public String toString() {
		return ("A rectangle with length " + getLength() + "and width of " + getWidth() + ", which is subclass of " + super.toString());
	}
}

class Square extends Rectangle{

	public Square() {
		super(1, 1);
	}
	
	public Square(double side) {
		super(side, side);
	}
	
	public Square(double side, String color, Boolean filled) {
		super(side, side, color, filled);
	}
	
	public double getSide() {
		return super.getWidth();
	}
	
	public void setSide(double side) {
		super.setLength(side);
		super.setWidth(side);
	}
	
	@Override
	public double getArea() {
		return super.getArea();
	}
	
	@Override
	public double getPerimeter() {
		return super.getPerimeter();
	}
	
	@Override
	public String toString() {
		return ("A square with side of " + getSide() + 
				"an area of " + getArea() + "and a parimeter of " + getPerimeter() + 
				"which is subclass of " + super.toString());
	}
}


// driver class 
public class ws3  
{ 
    public static void main(String args[])  
    { 
    	Shape s1 = new Shape();
    	System.out.println(s1.toString());	
    	Shape s2 = new Shape("yellow", false);
    	System.out.println(s2.toString());
    	System.out.println();
    	Shape circle1 = new Circle();
    	System.out.println(circle1.toString());
    	Shape circle2 = new Circle(2);
    	System.out.println(circle2.toString());
    	Shape circle3 = new Circle(3, "Red", false);
    	System.out.println(circle3.toString());
    	System.out.println();
    	Shape rect1 = new Rectangle();
    	System.out.println(rect1.toString());
    	Shape rect2 = new Rectangle(2, 3);
    	System.out.println(rect2.toString());
    	Shape rect3 = new Rectangle(4, 5, "blue", false);
    	System.out.println(rect3.toString());
    	System.out.println();
    	Shape square1 = new Square();
    	System.out.println(square1.toString());
    	Shape square2 = new Square(2);
    	System.out.println(square2.toString());
    	Shape square3 = new Square(4, "blue", false);
    	System.out.println(square3.toString());
    
        try {
	    	Class cl = Class.forName(args[0]);
	    	System.out.println("Name: " + cl.getName());
			System.out.println("class: " + args[0]);
			System.out.println("classes: " + cl.getClasses());
			System.out.println("annotations: " + cl.getAnnotations());
			System.out.println("constructor: " + cl.getConstructors());
			System.out.println("Feilds: " + cl.getFields());
			System.out.println("Methods: " + cl.getMethods());
			System.out.println("modifiers: " + cl.getModifiers());
        }
        
    	catch(ClassNotFoundException ex) {
            System.out.println(ex.toString());
        }
    }
} 