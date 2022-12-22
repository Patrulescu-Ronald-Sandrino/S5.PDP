namespace homework4
{
    internal static class Program
    {
        public static void Main(string[] args)
        {
            if (args.Length == 0)
                args = new[] { "www.google.com", "www.bing.com", "www.cs.ubbcluj.ro" };

            Impl1.Run(args);
            // Impl2.Run(args);
            // Impl3.Run(args);
        }
    }
}